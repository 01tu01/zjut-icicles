
/*
// ������ʵ����2�ο�����
*/

#include <stdio.h>
#include <stdlib.h>


//ջ��󳤶�
#define MAXSIZE  1024


//TODO: ����1����  datatype��SeqStack�Ķ��壬�Լ������Ƶ�ջ��������
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
    if (s == NULL || s->top == -1)
    {
        return 0;
    }
    *x = s->data[s->top];

    return 1;
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

/*
// ���ջ����Ϊchar�Ļ�����������
*/

/*-----------------------------------------------------------------------------------------------*/
// ��2�����ʽ��ֵ
/*-----------------------------------------------------------------------------------------------*/


//ջԪ������Ϊ����������
typedef int datatype2;

//ջ��Ϣ�ṹ��
typedef struct {
    datatype2 data[MAXSIZE];
    int  top;
} SeqStack2;


//��ʼ��ջ
SeqStack2* Init_SeqStack2()
{
    SeqStack2* s;
    s = (SeqStack2*)malloc(sizeof(SeqStack2));
    if (NULL == s)
    {
        return NULL;
    }
    s->top = -1;
    return s;
}


//�п�ջ
int Empty_SeqStack2(SeqStack2* s)
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
int Push_SeqStack2(SeqStack2* s, datatype2 x)
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
int Pop_SeqStack2(SeqStack2* s, datatype2* x)
{
    // TODO: �����ƣ�0.5�֣�
    if (s->top == -1)
    {
        return 0;
    }

    s->data[s->top] = 0;
    *x = s->data[s->top];
    s->top--;
    return 0;
}


//ȡջ��Ԫ��
int Top_SeqStack2(SeqStack2* s, datatype2* x)
{
    // TODO: �����ƣ�0.5�֣�
    if (s->top == -1 || s == NULL)
    {
        return 0;
    }

    *x = s->data[s->top];
    return 0;
}


//����ջ
int Destroy_Stack2(SeqStack2* s)
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


/*
// ����������������op_typeʵ�ֵ�һ������data1�͵ڶ�������data2֮�����������
*/
int operation(int data1, int data2, char op_type)
{
    int value;

    if (op_type == '+')
    {
        value = data1 + data2;
    }
    else if (op_type == '-')
    {
        value = data1 - data2;
    }
    else if (op_type == '*')
    {
        value = data1 * data2;
    }
    else if (op_type == '/')
    {
        value = data1 / data2;
    }

    printf("%d %c %d = %d\n", data1, op_type, data2, value);
    return value;
}

/*
// ��ȡ��������ȼ��ĺ���
*/
int get_level(char op_type)
{
    if (op_type == '*' || op_type == '/')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
// ���ʽ��ֵ��������
*/
void caculate_expression()
{
    SeqStack* S1;
    SeqStack2* S2;
    char input, op;
    int ret1, ret2, ret3;
    int value, cnt;
    int data1, data2;
    int err_flag;
    char buf[32];

    printf("���ʽ������Գ���ʼ:\n");

    //��ʼ��ջ1�����ڱ��������    
    S1 = Init_SeqStack();
    if (NULL == S1)
    {
        printf("������˳��ջ����ʧ��\n");
        return;
    }

    //��ʼ��ջ2�����ڱ��������    
    S2 = Init_SeqStack2();
    if (NULL == S2)
    {
        printf("������˳��ջ����ʧ��\n");
        return;
    }

    printf("������������ʽ�� \n");

    buf[0] = 0;
    cnt = 0;

    while (1)
    {
        input = getchar();
        //printf("%c \n", input);

        /*��������ַ�������н���*/
        if ('#' == input) /* �յ������� */
        {
            // ��ɲ��������ַ������ֵ�ת��
            if (cnt > 0)  /*�����#����ǰ�������ַ����룬�������ַ�ת��Ϊ��ֵ����ѹջ*/
            {
                buf[cnt] = 0;
                value = atoi(buf);
                Push_SeqStack2(S2, value);
                buf[0] = 0;
                cnt = 0;
            }

            //TODO: �����������㴦��1.5�֣�
            while (!Empty_SeqStack(S1))
            {

                Top_SeqStack2(S2, &data1);
                Pop_SeqStack2(S2, &ret2);
                Top_SeqStack2(S2, &data2);
                Pop_SeqStack2(S2, &ret2);

                Top_SeqStack(S1, &op);
                Push_SeqStack2(S2, operation(data2, data1, op));
                Pop_SeqStack(S1, &op);
            }
            break;
        }
        else if (input >= '0' && input <= '9')  /*��⵽�������ַ����Ƚ��������ַ����浽����buf��*/
        {
            buf[cnt] = input;
            cnt++;
        }
        else if ('+' == input || '-' == input || '*' == input || '/' == input)  /*��⵽��������*/
        {
            // ��ɽ����������ַ������ֵ�ת����ѹջ
            if (cnt > 0)
            {
                buf[cnt] = 0;
                value = atoi(buf);
                Push_SeqStack2(S2, value);
                buf[0] = 0;
                cnt = 0;
            }

            if (Top_SeqStack(S1, &op) == 1)  /*��������ջ�Ĳ�����*/
            {
                // TODO: ���ݵ�ǰ�����������ջ�������֮������ȼ��Ƚ�����������������㣨1.5�֣�
                if (get_level(op) == 1)
                {
                    Top_SeqStack2(S2, &data1);
                    Pop_SeqStack2(S2, &ret2);
                    Top_SeqStack2(S2, &data2);
                    Pop_SeqStack2(S2, &ret2);
                    Push_SeqStack2(S2, operation(data2, data1, op));

                    Pop_SeqStack(S1, &op);
                    Push_SeqStack(S1, input);
                }
                else
                {
                    Push_SeqStack(S1, input);
                }


            }
            else
            {
                /*����һ��������ѹջ*/
                Push_SeqStack(S1, input);
            }
        }
        else if (input == ' ')
        {
            if (cnt > 0) /*����ڿո�ǰ�������ַ����룬�������ַ�ת��Ϊ��ֵ����ѹջ*/
            {
                buf[cnt] = 0;
                value = atoi(buf);
                Push_SeqStack2(S2, value);
                buf[0] = 0;
                cnt = 0;
            }
            continue; /*����Ϊ�ո񣬼�������*/
        }
        else
        {
            printf("�����ַ�����,���������֡��Ӽ��˳��������ո񣬲���#�ż��ӻس�����\n");
            break;
        }

    }

    Top_SeqStack2(S2, &ret3);
    Pop_SeqStack2(S2, &ret1);

    if (Empty_SeqStack(S1) && Empty_SeqStack2(S2))
    {
        // TODO: ��ӡ���������ʽ����õ�����ֵ��0.5�֣�
        printf("���� = %d\n", ret3);

    }
    else
    {
        printf("������ʽ������!!!\n");
    }

    //����ջ
    Destroy_Stack(S1);
    Destroy_Stack2(S2);

    fflush(stdin);
    printf("���ʽ����������밴�������������\n");
    getchar();

}


void main()
{
    caculate_expression();
}

