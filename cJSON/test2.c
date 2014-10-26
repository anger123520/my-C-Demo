#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"

/*
"{
"operatorNums":2,
"operatorInfos":[{"operatorID": 1, "operatorInfo": "shandong"}, {"operatorID": 2, "operatorInfo": "shandong"}]
}"
*/

/*
{¡°dvb-c¡±:
[
{¡°status¡±:¡±locked¡±,¡°frequency¡±:¡±538000¡±,¡±symbolrate¡±:¡±6875¡±,¡±qam¡±:¡±qam64¡±,¡±strength¡±:¡±80¡±,¡±quality¡±:¡±100¡±,¡± BER¡±:¡±10e-9¡±,¡± SNR¡±:¡±0¡±},
{¡°status¡±:¡±locked¡±,¡°frequency¡±:¡±530000¡±,¡±symbolrate¡±:¡±6875¡±,¡±qam¡±:¡±qam64¡±,¡±strength¡±:¡±80¡±,¡±quality¡±:¡±100¡±,¡± BER¡±:¡±10e-9¡±,¡± SNR¡±:¡±0¡±},
{¡°status¡±:¡±locked¡±,¡°frequency¡±:¡±546000¡±,¡±symbolrate¡±:¡±6875¡±,¡±qam¡±:¡±qam64¡±,¡±strength¡±:¡±80¡±,¡±quality¡±:¡±100¡±,¡± BER¡±:¡±10e-9¡±,¡± SNR¡±:¡±0¡±},
]
}
*/
typedef struct _operator_
{
	int id;
	char name[10];
}Operator;

void create_objects()
{   
    cJSON *root,*fmt,*img,*thm,*fld;char *out;int i;    /* declare a few. */
   
    /* Here we construct some JSON standards, from the JSON site. */
 	Operator operator_info[2] = {{1,"shandong"},{2, "shandong2"}};
    root=cJSON_CreateObject();
    cJSON_AddItemToObject(root, "operatorNums", cJSON_CreateNumber(2));
    cJSON_AddItemToObject(root, "operatorInfos", fmt=cJSON_CreateArray());
	for(i = 0; i < 2; i++)
	{
		cJSON_AddItemToArray(fmt,fld=cJSON_CreateObject());
		cJSON_AddNumberToObject(fld, "operatorID", operator_info[i].id);
		cJSON_AddStringToObject(fld, "operatorInfo", operator_info[i].name);
	}
	out=cJSON_PrintUnformatted(root);	cJSON_Delete(root);	printf("%s\n",out);	free(out);
	
	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "dvb-c", fmt=cJSON_CreateArray());
	for(i = 0; i < 2; i++)
	{
	    cJSON_AddItemToArray(fmt,fld=cJSON_CreateObject());
	    cJSON_AddStringToObject(fld, "status", "locked");
	    cJSON_AddStringToObject(fld, "frequency", "530000");
	    cJSON_AddStringToObject(fld, "symbolrate", "6875");
	    cJSON_AddStringToObject(fld, "qam", "qam64");
	    cJSON_AddStringToObject(fld, "strength", "80");
	    cJSON_AddStringToObject(fld, "quality", "100");
	    cJSON_AddStringToObject(fld, "BER", "10e-9");
	    cJSON_AddStringToObject(fld, "SNR", "");
	}
	out=cJSON_Print(root);	cJSON_Delete(root);	printf("%s\n",out);	free(out);
	
}

void Parse_objects(char *text)
{
    char *out;cJSON *json, *pItem;
    int flag = 0;
    char time[20] = {0};
    json=cJSON_Parse(text);
	if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
	else
	{
	    pItem = cJSON_GetObjectItem(json, "flag");
	    flag = pItem->valueint;
	    //cJSON_Delete(json);
	    printf("[%s] flag = %d\n",__FUNCTION__,flag);
	    pItem = cJSON_GetObjectItem(json, "starttime");
	    strncpy(time, pItem->valuestring, strlen(pItem->valuestring));
	    printf("starttime=%s \n",time);
	    cJSON_Delete(json);
	}
	
	return;
}

int main(int argc, char **argv)
{
    char text1[] = "{\"pincode\": \"1234\", \"flag\": 1, \"starttime\": \"20140908070605\", \"endtime\": \"20140908112233\",\"startchan\": 1, \"endchan\": 2, \"status\": 1}";
	/* Now some samplecode for building objects concisely: */
	create_objects();
	
	/* Process each json textblock by parsing, then rebuilding: */
	Parse_objects(text1);
	return 0;
}
