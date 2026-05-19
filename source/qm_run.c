/*
Copyright (c) 2025 Sarash Basumatary

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include "qmMinimizer.h"
#include "cJSON.h"
#include "qmdata_to_json.h"
#include "parse_input.h"
#include "qm_run.h"

char *qm_run(const char *input)
{
    char *errorMsg = NULL;
	int var = 0, *minterms = NULL, minCount = 0 , *dontCares = NULL, dontCareCount = 0;

	cJSON *qmData_json = NULL;
	qmData data = {0};

	if(!input){
		errorMsg =  "Failed to read input";
		goto FAIL;
	}

	int error = parse_input_json(input, &var, &minterms, &minCount, &dontCares, &dontCareCount);
	if(error == 1){
		errorMsg = "Parsing input failed due to invalid json";
		goto FAIL;
	}
	else if(error == 2){
		errorMsg = "Invalid input variable or not Found";
		goto FAIL;
	}
	else if(error == 3){
		errorMsg = "memory Allocation fail";
		goto FAIL;
	}
	else if(error == 4){
		errorMsg = "Invalid Datatypes Found";
		goto FAIL;
	}

	int *tmp = realloc(minterms, (minCount + dontCareCount) * sizeof(*tmp));
	if(!tmp) goto FAIL;
	minterms = tmp;

	//inserting dontcare elements at the end of minterms
	for(int i = 0; i < dontCareCount; i++)
		minterms[minCount + i] = dontCares[i];

	//call minimizer
	data = qmMinimizer(minterms, minCount,dontCares, dontCareCount, var);
	if(data.error){
		errorMsg = data.errorMsg;
		goto FAIL;
	}

	minterms = NULL;
	dontCares = NULL;

	//convert to json
	qmData_json = qmData_to_json(&data);
	if(!qmData_json){
		errorMsg = "cJSON Output Failed";
		goto FAIL;
	}

	char *out = cJSON_Print(qmData_json);

	cJSON_Delete(qmData_json);
	destroyQmData(&data);

	return out;

	FAIL:
		cJSON_Delete(qmData_json);
		destroyQmData(&data);

		cJSON *error_json = cJSON_CreateObject();
		cJSON_AddBoolToObject(error_json , "error" , 1);
		cJSON_AddStringToObject(error_json , "errorMsg" , errorMsg);

		out = cJSON_Print(error_json);
		cJSON_Delete(error_json);

		return out;
}
