#ifndef __CMD_H
#define __CMD_H

#include "sys.h"

#define MAX_CMD_NAME_LENGH   	30 //������������
#define MAX_CMD_NUM					 	20 //����������

typedef void (*handler)(void);

typedef struct cmd
{
	char cmd_name[MAX_CMD_NAME_LENGH+1];//���������
	handler cmd_fops;//����Ĳ�������
}cmd;

typedef struct cmd_list
{
	cmd cmds[MAX_CMD_NUM];//������б�
	int num;//����ĸ���������
}cmd_l;

void register_cmd(cmd reg_cmd[],int num);
void match_cmd(char *str);


#endif



