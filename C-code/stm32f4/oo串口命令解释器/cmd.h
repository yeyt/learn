#ifndef __CMD_H
#define __CMD_H

#include "sys.h"

#define MAX_CMD_NAME_LENGH   	30 //最大的命令名称
#define MAX_CMD_NUM					 	20 //最大的命令数

typedef void (*handler)(void);

typedef struct cmd
{
	char cmd_name[MAX_CMD_NAME_LENGH+1];//命令的名称
	handler cmd_fops;//命令的操作函数
}cmd;

typedef struct cmd_list
{
	cmd cmds[MAX_CMD_NUM];//命令的列表
	int num;//命令的个数，计数
}cmd_l;

void register_cmd(cmd reg_cmd[],int num);
void match_cmd(char *str);


#endif



