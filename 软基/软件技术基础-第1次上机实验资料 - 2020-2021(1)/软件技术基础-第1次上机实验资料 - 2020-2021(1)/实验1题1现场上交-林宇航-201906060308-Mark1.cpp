
/*
// ʵ��ο�����
*/

#include <stdio.h>
#include <stdlib.h>



/*-----------------------------------------------------------------------------------------------*/
// ��Ŀ������������
/*-----------------------------------------------------------------------------------------------*/


/*
// �������㶨��
*/
typedef struct node
{
    int data;
    struct node* next;
}NODE;



/*
// β�������㽨����ͷ���ĵ�������
*/
NODE* create_nodes_list()
{
    NODE* H = NULL;
    NODE* s, * r = NULL;
    int ret, data;
    char exit_flag;

    H = (NODE*)malloc(sizeof(NODE));
    if (H == NULL)
    {
        return NULL;
    }

    /*��ʼ��ͷ������*/
    H->data = 0;
    H->next = NULL;

    r = H;

    printf("�����뵥�����������,ֱ������q�ӻس���������\n");
    while (1)
    {
        ret = scanf_s("%d", &data);
        scanf_s("%c", &exit_flag);

        if (ret == 1)
        {
            s = (NODE*)malloc(sizeof(NODE));
            if (s == NULL)
            {
                break;
            }
            s->data = data;
            s->next = NULL; /*�´��������ڶ�β����ʼ��ָ����Ϊ��*/

            r->next = s;

            /*rָ���β�Ľ��*/
            r = s;
        }
        else if (exit_flag == 'q')
        {
            printf("����һԪ����ʽ�������\n");
            break;
        }
        else
        {
            printf("������������밴Ҫ��������ֵ������������ֱ������q�ӻس�\n");
        }

        fflush(stdin);
    }

    return H;
}


/*
// ������ӡ��ͷ��������������������
*/
void print_nodes_list(NODE* H)
{
    NODE* p;

    if (H == NULL)
    {
        return;
    }

    p = H->next;

    printf("�������������ֵ���£�\n");

    // TODO��1�֣�
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }

    printf("\n");
}



/*
// ���ٴ�ͷ����������
*/
void destroy_nodes_list(NODE* H)
{
    NODE* t, * p;

    if (H == NULL)
    {
        return;
    }

    p = H;

    // TODO��1�֣�
    t = p->next;
    while (t)
    {
        delete p;
        p = t;
        t = p->next;
    }
}



/*
// ����������
*/
void reverse_list(NODE* H)
{

    // TODO��3�֣�: ʵ�ֵ���������
    if (H == NULL)
    {
        return;
    }
    NODE* p = H->next;

    int data[100], i = -1;

    while (p)
    {
        i++;
        data[i] = p->data;
        p = p->next;
    }
    p = H->next;
    while (p)
    {
        p->data = data[i];
        i--;
        p = p->next;
    }

    return;
}



/*
// ������������Ժ���
*/
void test_reverse_list()
{
    NODE* pa = NULL;

    /*��������A*/
    printf("\n");
    printf("��������\n");
    pa = create_nodes_list();

    /*�����������������*/
    printf("\n");
    printf("����֮ǰ����������:\n");
    print_nodes_list(pa);

    /*��������*/
    reverse_list(pa);

    /*��ӡ�������֮�������*/
    printf("\n");
    printf("����֮����������ݣ�\n");
    print_nodes_list(pa);

    /*��������*/
    destroy_nodes_list(pa);

    getchar();
}


void main()
{
    /*���Ե���������*/
    test_reverse_list();

}

