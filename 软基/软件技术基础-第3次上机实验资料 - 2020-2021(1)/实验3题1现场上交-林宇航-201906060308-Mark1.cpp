
/*
// ������ʵ����Ŀ1�ο�����
*/

#include <stdio.h>
#include <stdlib.h>


//ջ��󳤶�
#define MAXSIZE  1024


/*
// ���ջ����Ϊchar�Ļ�����������
*/

//ջԪ������Ϊ�ַ�������
typedef char datatype;

//ջ��Ϣ�ṹ��
typedef struct {
    datatype data[MAXSIZE];
    int  top;
} SeqStack;


//��ʼ��ջ
SeqStack* Init_SeqStack()
{
    SeqStack* s;
    s = (SeqStack*)malloc(sizeof(SeqStack));
    if (NULL == s)
    {
        return NULL;
    }
    s->top = -1;
    return s;
}


//�п�ջ
int Empty_SeqStack(SeqStack* s)
{
    if (-1 == s->top)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//��ջ
int Push_SeqStack(SeqStack* s, datatype x)
{
    // TODO: �����ƣ�0.5�֣�
    if (s->top == MAXSIZE)
    {
        return 0;
    }
    s->data[s->top + 1] = x;
    s->top++;

    return 0;
}


//��ջ
int Pop_SeqStack(SeqStack* s, datatype* x)
{
    // TODO: �����ƣ�0.5�֣�
    if (Empty_SeqStack(s))
    {
        return 0;
    }
    *x = s->data[s->top];
    s->data[s->top] = ' ';
    s->top--;
    return 0;
}


//ȡջ��Ԫ��
int Top_SeqStack(SeqStack* s, datatype* x)
{
    // TODO: �����ƣ�0.5�֣�
    if (s == NULL)
    {
        return 0;
    }
    *x = s->data[s->top];

    return 0;
}


//����ջ
int Destroy_Stack(SeqStack* s)
{
    if (NULL == s)
    {
        return 0;
    }
    else
    {
        free(s);
        return 1;
    }
}


/*-----------------------------------------------------------------------------------------------*/
// ��1�������������ƥ��״��
/*-----------------------------------------------------------------------------------------------*/

void check_brackets()
{
    SeqStack* S;
    datatype input, topdata;
    int ret = 0;

    printf("���ż����Գ���ʼ:\n");


    //��ʼ��ջ    
    //TODO��0.5�֣�
    S = Init_SeqStack();
    printf("֧�ֵ����Ű�����%c, %c, %c, %c, %c, %c \n", '(', ')', '[', ']', '{', '}');
    printf("������������ʽ�� \n");
    while (1)
    {
        input = getchar();

        /*��������ַ�������н���*/
        if (input == '#')
        {
            //��⵽�����ַ�������ѭ��
            break;
        }
        else
        {
            // TODO: ����input��ֵ�������б�����2�֣�
            if (input == '(' || input == '[' || input == '{')
            {
                Push_SeqStack(S, input);
            }
            else if (input == ')' || input == ']' || input == '}')
            {
                Top_SeqStack(S, &topdata);
                if (topdata == input - 1 || topdata == input - 2)
                {
                    Pop_SeqStack(S, &topdata);
                }
                else
                {
                    ret = 1;
                    break;
                }
            }
        }
    }


    /*��Empty_SeqStack()�����б������Ƿ���ȷƥ��*/
    //TODO��0.5�֣�
    if (ret == 1 || Empty_SeqStack(S) == 0)
    {
        printf("������ʽ���Ų�ƥ��!!!\n");
    }
    else
    {
        printf("������ʽ����ƥ��\n");
    }

    //����ջ
    //TODO��0.5�֣�
    Destroy_Stack(S);

    fflush(stdin);
    printf("����������ż��������밴�������������\n");
    getchar();

    return;
}


void main()
{
    check_brackets();
}

