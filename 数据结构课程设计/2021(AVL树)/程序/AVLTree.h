//
// Created by Dylan on 2021/12/15.
//

#ifndef AVL_AVLTREE_H
#define AVL_AVLTREE_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Node.h"

class AVLTree {
private:
    Node *root = nullptr;  //ָ������
    int depth = 0;  //�����������
    bool sign = false;  //��¼�����Ƿ�ɹ�

    // һ�����飬��ӡ�ã����鳤�Ȳ����ڶ������ĸ߶ȣ���Ϊһ��
    // ��ǵ�ǰ�Ľڵ��Ǹ��ڵ�����ӻ����Һ���
    int vec_left[100] = {0};

    void printAVL(Node *node, int sign = 0);  //��ӡ������
    void deleteNode(Node *node, string usn, Node *p = nullptr);  //ɾ�����
    void add(Node *T, Node *newNode, Node *parent= nullptr);  //��ӽ��
    void updatePassword(string usn, string pwd, Node *T);  //��������
    void login(string usn, string pwd, Node *T);  //��¼
    void save(ofstream &outFile, Node *T);
public:
    AVLTree(ifstream &inFile);  //ʹ���ļ������ʼ��������
    ~AVLTree();  //���������ͷ�

    void save(ofstream &outFile);  //���û���Ϣ�����ļ�
    void print();  //��װ��Ĵ�ӡ����

    bool getSign();  //�жϲ����Ƿ�ɹ�
    void reSign();  //���ñ�־

    int getHeight(Node *T);  //��ȡ���ĸ߶�
    void deleteNode(string usn);  //��װ���ɾ����㺯��
    void add(string usn, string pwd);  //��װ�����ӽ�㺯��
    void updatePassword(string usn, string pwd);  //��װ��ĸ������뺯��
    void login(string usn, string pwd);  //��װ��ĵ�¼����

    void RRotate(Node *node, Node *parent);  //����
    void LRotate(Node *node, Node *parent);  //����
};


#endif //AVL_AVLTREE_H
