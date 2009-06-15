/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Spring 2009                                          */
/*                                                                         */
/* Homework : Wet 2                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main2.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "library2.h"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif




/* The command's strings */
typedef enum {
  NONE_CMD = -2,
  COMMENT_CMD = -1,
  INIT_CMD = 0,
  ADDTOWN_CMD = 1,
  ADDROAD_CMD = 2,
  REMOVEROAD_CMD = 3,
  ADDBORDER_CMD = 4,
  REMOVEBORDER_CMD = 5,
  ADDNEIGHBORHOOD_CMD = 6,
  ADDMANYNEIGHBORHOODS_CMD = 7,
  MONSTERATTACK_CMD = 8,
  CHANGEMA_CMD = 9,
  QUIT_CMD = 10
} commandType;



static const int   numActions   = 11;
static const char *commandStr[] = {
  "Init",
  "AddTown",
  "AddRoad",
  "RemoveRoad",
  "AddBorder",
  "RemoveBorder",
  "AddNeighborhood",
  "AddManyNeighborhoods",
  "MonsterAttack",
  "ChangeMa",
  "Quit"
};


static const char* ReturnValToStr(int val) {
	switch (val) {
		case (SUCCESS):          return "Success";
		case (FAILURE):          return "Failure";
		case (INVALID_INPUT):    return "Invalid_input";
		default:                 return "";
	}
}
	





/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {error_free, error} errorType;
static errorType parser(const char* const command);



#define ValidateRead(read_parameters,required_parameters,ErrorString) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString); return error; }


static bool isInit = false;


/* Print an array */
string PrintIntArray(const int* arr, int size) {
	char buffer[MAX_BUFFER_SIZE];
	string str = "";

	for (int i=0; i < size; i++) {
		sprintf(buffer,"%d",arr[i]);
		str += string(buffer) + ((i == (size - 1)) ? "" : ",");
	}
	return str.c_str();
}




/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {
  char buffer[MAX_STRING_INPUT_SIZE];
  // Reading commands
  while ( fgets(buffer, MAX_STRING_INPUT_SIZE, stdin) != NULL ) {
    fflush(stdout); 
    if ( parser(buffer) == error )
      break;
  };
  return 0;
}

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command, const char** const command_arg) {
  if ( command == NULL || strlen(command) == 0 || StrCmp("\n", command) )
    return(NONE_CMD);
  if ( StrCmp("#", command) ) {
    if (strlen(command) > 1)
      printf("%s", command);
    return(COMMENT_CMD);
  };
  for (int index=0; index < numActions; index++) {
    if ( StrCmp(commandStr[index], command) ) {
      *command_arg = command + strlen(commandStr[index]) + 1;
      return((commandType)index);
    };
  };
  return(NONE_CMD);
}

/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddTown(void* DS, const char* const command);
static errorType OnAddRoad(void* DS, const char* const command);
static errorType OnRemoveRoad(void* DS, const char* const command);
static errorType OnAddBorder(void* DS, const char* const command);
static errorType OnRemoveBorder(void* DS, const char* const command);
static errorType OnAddNeighborhood(void* DS, const char* const command);
static errorType OnAddManyNeighborhoods(void* DS, const char* const command);
static errorType OnMonsterAttack(void* DS, const char* const command);
static errorType OnChangeMa(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);




/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) { 
  static void *DS = NULL; /* The general data structure */
  const char* command_args = NULL;
  errorType rtn_val = error;

  commandType command_val = CheckCommand(command, &command_args);
 
  switch (command_val) {

	case (INIT_CMD):                   rtn_val = OnInit(&DS, command_args);	break;
	case (ADDTOWN_CMD):                rtn_val = OnAddTown(DS, command_args);	break;
	case (ADDROAD_CMD):                rtn_val = OnAddRoad(DS, command_args);	break;
	case (REMOVEROAD_CMD):             rtn_val = OnRemoveRoad(DS, command_args);	break;
	case (ADDBORDER_CMD):              rtn_val = OnAddBorder(DS, command_args);	break;
	case (REMOVEBORDER_CMD):           rtn_val = OnRemoveBorder(DS, command_args);	break;
	case (ADDNEIGHBORHOOD_CMD):        rtn_val = OnAddNeighborhood(DS, command_args);	break;
	case (ADDMANYNEIGHBORHOODS_CMD):   rtn_val = OnAddManyNeighborhoods(DS, command_args);	break;
	case (MONSTERATTACK_CMD):          rtn_val = OnMonsterAttack(DS, command_args);	break;
	case (CHANGEMA_CMD):               rtn_val = OnChangeMa(DS, command_args);	break;
	case (QUIT_CMD):                   rtn_val = OnQuit(&DS, command_args);	break;
	
	case (COMMENT_CMD):                rtn_val = error_free;	break;
	case (NONE_CMD):                   rtn_val = error;	break;
	default: assert(false);
  };
  return(rtn_val);
}





/***************************************************************************/
/* OnInit                                                                  */
/***************************************************************************/
static errorType OnInit(void** DS, const char* const command) {
	if(isInit) {
		printf("Init was already called.\n");
		return(error_free);
	};
	isInit = true;

	int	ma;	
	ValidateRead( sscanf(command, "%d" ,&ma), 1, "Init failed.\n" );
		
	*DS = Init(ma);
	if( *DS == NULL ) {
		printf("Init failed.\n");
		return(error);
	};
	printf("Init done.\n");

	return error_free;
}


/***************************************************************************/
/* OnAddTown                                                               */
/***************************************************************************/
static errorType OnAddTown(void* DS, const char* const command) {
	int side;
	int location;
	int maxNeighborhoods;
	ValidateRead( sscanf(command, "%d %d %d",&side,&location,&maxNeighborhoods), 3, "AddTown failed.\n" );
	StatusType res = AddTown(DS,(Shore)side,location,maxNeighborhoods);
	
	if (res != SUCCESS) {
		printf("AddTown: %s\n",ReturnValToStr(res));
	}
	else {
		printf("AddTown: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnAddRoad                                                               */
/***************************************************************************/
static errorType OnAddRoad(void* DS, const char* const command) {
	int northTown;
	int southTown;
	ValidateRead( sscanf(command, "%d %d",&northTown,&southTown), 2, "AddRoad failed.\n" );
	StatusType res = AddRoad(DS,northTown,southTown);
	
	if (res != SUCCESS) {
		printf("AddRoad: %s\n",ReturnValToStr(res));
	}
	else {
		printf("AddRoad: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnRemoveRoad                                                            */
/***************************************************************************/
static errorType OnRemoveRoad(void* DS, const char* const command) {
	int northTown;
	int southTown;
	ValidateRead( sscanf(command, "%d %d",&northTown,&southTown), 2, "RemoveRoad failed.\n" );
	StatusType res = RemoveRoad(DS,northTown,southTown);
	
	if (res != SUCCESS) {
		printf("RemoveRoad: %s\n",ReturnValToStr(res));
	}
	else {
		printf("RemoveRoad: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnAddBorder                                                             */
/***************************************************************************/
static errorType OnAddBorder(void* DS, const char* const command) {
	int northPt;
	int southPt;
	ValidateRead( sscanf(command, "%d %d",&northPt,&southPt), 2, "AddBorder failed.\n" );
	StatusType res = AddBorder(DS,northPt,southPt);
	
	if (res != SUCCESS) {
		printf("AddBorder: %s\n",ReturnValToStr(res));
	}
	else {
		printf("AddBorder: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnRemoveBorder                                                          */
/***************************************************************************/
static errorType OnRemoveBorder(void* DS, const char* const command) {
	int northPt;
	int southPt;
	ValidateRead( sscanf(command, "%d %d",&northPt,&southPt), 2, "RemoveBorder failed.\n" );
	StatusType res = RemoveBorder(DS,northPt,southPt);
	
	if (res != SUCCESS) {
		printf("RemoveBorder: %s\n",ReturnValToStr(res));
	}
	else {
		printf("RemoveBorder: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnAddNeighborhood                                                       */
/***************************************************************************/
static errorType OnAddNeighborhood(void* DS, const char* const command) {
	int side;
	int location;
	int population;
	ValidateRead( sscanf(command, "%d %d %d",&side,&location,&population), 3, "AddNeighborhood failed.\n" );
	StatusType res = AddNeighborhood(DS,(Shore)side,location,population);
	
	if (res != SUCCESS) {
		printf("AddNeighborhood: %s\n",ReturnValToStr(res));
	}
	else {
		printf("AddNeighborhood: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* Parsing special input necessary at AddManyNeighborhoods                 */
/***************************************************************************/
static errorType ParseAddManyNeighborhoodsInput(const char* const command, 
                                    int* side, int* location, int* size, int** populations) {
    int i = 0;
    int readSoFar = 0;
    int readSoFar2 = 0;
    int pop;
    ValidateRead( sscanf(command, "%d %d %d %n",side,location,size, &readSoFar), 3, "AddManyNeighborhoods failed.\n" );

    *populations = (int*)malloc(sizeof(int)*(*size));
    while (i < *size) {
        ValidateRead( sscanf(command+readSoFar, "%d %n", &pop, &readSoFar2), 1, "AddManyNeighborhoods failed.\n" );    
        readSoFar += readSoFar2;
        
        (*populations)[i] = pop;

        i++;
    }

    return error_free;
}

/***************************************************************************/
/* OnAddManyNeighborhoods                                                  */
/***************************************************************************/
static errorType OnAddManyNeighborhoods(void* DS, const char* const command) {
	int side;
	int location;
	int size;
	int* populations;

    errorType res1 = ParseAddManyNeighborhoodsInput(command, &side, &location, &size, &populations);
    if (res1 != error_free)
        return res1;

    StatusType res = AddManyNeighborhoods(DS,(Shore)side,location,size,populations);
	
    free(populations);

	if (res != SUCCESS) {
		printf("AddManyNeighborhoods: %s\n",ReturnValToStr(res));
	}
	else {
		printf("AddManyNeighborhoods: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnMonsterAttack                                                         */
/***************************************************************************/
static errorType OnMonsterAttack(void* DS, const char* const command) {
	int side;
	int location;
	ValidateRead( sscanf(command, "%d %d",&side,&location), 2, "MonsterAttack failed.\n" );
	int	population;
	StatusType res = MonsterAttack(DS,(Shore)side,location,&population);
	
	if (res != SUCCESS) {
		printf("MonsterAttack: %s\n",ReturnValToStr(res));
	}
	else {
		printf("MonsterAttack: %s %d\n", ReturnValToStr(res),population);
	}

	return error_free;
}


/***************************************************************************/
/* OnChangeMa                                                              */
/***************************************************************************/
static errorType OnChangeMa(void* DS, const char* const command) {
	int ma;
	ValidateRead( sscanf(command, "%d",&ma), 1, "ChangeMa failed.\n" );
	StatusType res = ChangeMa(DS,ma);
	
	if (res != SUCCESS) {
		printf("ChangeMa: %s\n",ReturnValToStr(res));
	}
	else {
		printf("ChangeMa: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnQuit                                                                  */
/***************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
	Quit(DS);
	if( *DS != NULL ) {
		printf("Quit failed.\n");
		return(error);
	};
	isInit = false;
	printf("Quit done.\n");

	return error_free;
}




#ifdef __cplusplus
}
#endif


