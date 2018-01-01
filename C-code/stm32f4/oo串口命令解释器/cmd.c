#include "string.h"
#include "cmd.h"
#include "sys.h"

static cmd_l cmd_array = { NULL ,0 };


void register_cmd(cmd reg_cmd[],int num)	
{
	int i;
	if( num> MAX_CMD_NUM )
	{
		return ;
	}
	for(i=0;i<num;i++)
	{
		if(cmd_array.num < MAX_CMD_NUM)
		{
			strcpy(cmd_array.cmds[cmd_array.num].cmd_name,reg_cmd[i].cmd_name);
			cmd_array.cmds[cmd_array.num].cmd_fops=reg_cmd[i].cmd_fops;
			cmd_array.num++;
		}
	}
}

void match_cmd(char *str)
{
	int i;
	if((strlen(str) > MAX_CMD_NAME_LENGH) || (cmd_array.num ==0))
	{
		return ;
	}
	
	for(i=0;i<cmd_array.num;i++)
	{
		
		if(strcmp(cmd_array.cmds[i].cmd_name,str) ==0 )
		{
			cmd_array.cmds[i].cmd_fops();
		}
	}
}




