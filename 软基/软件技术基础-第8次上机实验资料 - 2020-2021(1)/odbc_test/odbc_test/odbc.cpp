#include <iostream>
#include <windows.h>
#include "sql.h"        
#include "sqlext.h"     
#include "sqltypes.h"  
#include "sqlucode.h"  
#include "odbcss.h"    
#include "tchar.h"
#include "stdio.h"
using namespace std;

void main()
{
	SQLHENV henv;
 	SQLRETURN rev;
	SQLHDBC hdbc;
 	char sqlString[255];
 	SQLHSTMT hStmt;

 	SQLCHAR szBuff[128];
 	SQLCHAR CBuff[128];
 	SQLINTEGER  nReadBytes;
 	SQLRETURN     nRC; 

 	cout<<"ʹ��ODBC API�����������ݿ�ѧϰ\n";
 	rev = SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&henv);
 	if(rev == SQL_SUCCESS_WITH_INFO || rev == SQL_SUCCESS)
 	{
  		cout<<"���价���ɹ�\n";
 	}
	else
 	{
  		cout<<"���价��ʧ��\n";
  		return;
 	}
 	rev = SQLSetEnvAttr(henv,SQL_ATTR_ODBC_VERSION,(void *)SQL_OV_ODBC3,0);
 	if(rev == SQL_SUCCESS || rev == SQL_SUCCESS_WITH_INFO)   
 	{   
    	rev=SQLAllocHandle(SQL_HANDLE_DBC,henv,&hdbc);
    	if(rev == SQL_SUCCESS_WITH_INFO || rev == SQL_SUCCESS)
    	{
      		cout<<"�������Ӿ���ɹ�\n";
    	}
    	else
    	{
      		cout<<"�������Ӿ��ʧ��\n"; 
      		SQLFreeHandle(SQL_HANDLE_ENV, henv);
      		return;
    	}
 	}

 	/*�������ݿ⣬�ر�ע�⣺sql_zjut_eduΪODBC�����õ����ݿ����ƣ���Ҫ����ʵ���������滻*/
 	rev = SQLConnect(hdbc,(SQLCHAR *)"JXGL8",SQL_NTS,(SQLCHAR *)"",SQL_NTS,(SQLCHAR *)"",SQL_NTS);
 	if(rev == SQL_SUCCESS_WITH_INFO || rev == SQL_SUCCESS)
 	{
  		cout<<"���ݿ����ӳɹ�\n";
 	}
 	else
 	{
  		cout<<"���ݿ�����ʧ��\n";
  		SQLFreeHandle(SQL_HANDLE_DBC, hdbc);       
  		SQLFreeHandle(SQL_HANDLE_ENV, henv);
  		system("pause");
  		return;
 	}
 
 	rev = SQLAllocStmt(hdbc, &hStmt); 

 	/*��S���в�ѯ��Ϊ���ε�ѧ��ѧ��*/ 
 	sprintf_s(sqlString,"select S# from S where SNAME = '����'");
 	rev = SQLExecDirect(hStmt,(SQLCHAR *)sqlString,SQL_NTS);
 	if(rev == SQL_SUCCESS)
 	{
 	 
        while ( (nRC = SQLFetch(hStmt)) != SQL_NO_DATA)
  		{
     		//TODO:��ȡ���ε�ѧ�� ������szBuff 
       
            SQLGetData(hStmt, 1, SQL_C_CHAR, &szBuff, 128, &nReadBytes);

   		}
        
   		printf("%s\n",szBuff);
 	}
 	else
 	{
  		cout<<"ִ��ʧ��!"<<endl;
 	}

 
 	rev = SQLAllocStmt(hdbc, &hStmt); 
 	//TODO:��C���в�ѯ���������Ŀγ̺� 
    

    sprintf_s(sqlString, "select CLASSH from C where CNAME = '���������'");
    rev = SQLExecDirect(hStmt, (SQLCHAR*)sqlString, SQL_NTS);
 	if(rev == SQL_SUCCESS)
 	{   
  		cout<<"ִ��SQL���ɹ�!"<<endl;
        //TODO:��ȡ���������Ŀγ̺� ������CBuff
        while ((nRC = SQLFetch(hStmt)) != SQL_NO_DATA)
        {
            SQLGetData(hStmt, 1, SQL_C_CHAR, &CBuff, 128, &nReadBytes);
        }

   		printf("%s\n",CBuff);
 	}
 	else
 	{
  		cout<<"ִ��ʧ��!"<<endl;
 	}

 	rev = SQLAllocStmt(hdbc, &hStmt); 
 
 	//TODO: ����SC�������������γ̺ź�����ѧ�Ŷ�Ӧ�ķ�����2�� 

 
 	if(rev == SQL_SUCCESS)
 	{
  		cout<<"ִ��SQL���ɹ�!"<<endl;
 	}
 	else
	 	cout<<"ִ��ʧ��!"<<endl;
  	/*�����ڴ�*/
  	if (hStmt != SQL_NULL_HSTMT) 
  	{
    	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    	hStmt = SQL_NULL_HSTMT;
  	}
  	SQLDisconnect(hdbc);
  	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);       
  	SQLFreeHandle(SQL_HANDLE_ENV, henv);

  	system("pause");
  	return;
}
