//
// Created by Dylan on 2021/12/15.
//

#ifndef AVL_NODE_H
#define AVL_NODE_H
#include <string>
using namespace std;
struct userInfo{  //�û����ݽṹ��
    string username;
    string password;
};

class Node {
private:
    int bf = 0;  //���ƽ������
    Node *lChild = nullptr, *rChild = nullptr;  //���Һ���ָ��
    userInfo user;  //�û���Ϣ

public:
    Node(string usn, string pwd);  //��ʼ��
    userInfo& getUser();  //��ȡ�û���Ϣ
    Node* getLChild();  //��ȡ����
    Node* getRChild();  //��ȡ�Һ���
    int getBF();  //��ȡƽ������
    void setBf(int bf);  //����ƽ������
    void setLChild(Node* newNode);  //�������
    void setRChild(Node* newNode);  //����Һ���
    ~Node();  //�ͷŽ��
};


#endif //AVL_NODE_H
