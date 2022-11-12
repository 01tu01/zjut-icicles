//
// Created by Dylan on 2021/12/15.
//

#include "AVLTree.h"
AVLTree::AVLTree(ifstream &inFile) {
    string tempstr;  //��ȡ�ַ���
    int searchBound;  //��¼�ַ����ָ��־"@"��λ��
    Node *temp;  //�½��ָ��

    //�û���ʼ��
    while(inFile.peek() != EOF){  //����ļ��Ƿ񵽵�
        //�ַ�����
        inFile>>tempstr;
        searchBound = tempstr.find('@');

        //�½���㲢��ʼ��
        temp = new Node(tempstr.substr(0,searchBound),  //��ȡ�û���
                        tempstr.substr(searchBound+1,tempstr.length()-searchBound-1)  //��ȡ����
                        );

        //�����в����½��
        add(root, temp);
    }
    sign = false;
}

AVLTree::~AVLTree() {

}

void AVLTree::printAVL(Node *node, int sign) {
    if(sign> 0){  //�����ĸ߶ȴ���0ʱ
        for(int i = 0; i < sign - 1; i++){
            printf(vec_left[i] ? "��   " : "    ");
        }
        printf(vec_left[sign-1] ? "������ " : "������ ");
    }

    if(! node){  //����㲻���ڵ�ʱ��
        printf("(null)\n");
        return;
    }

    //��ӡ��ǰ�������
    printf("%s\n", node->getUser().username.c_str());

    //��ǰ���ΪҶ�ӽ��ʱ����
    if(!node->getLChild() && !node->getRChild()){
        return;
    }

    vec_left[sign] = 1; //���뵱ǰ�����Һ���
    printAVL(node->getRChild(), sign + 1);
    vec_left[sign] = 0; //���뵱ǰ��������
    printAVL(node->getLChild(), sign + 1);

}

void AVLTree::print() {  //��װ��Ĵ�ӡ����
    printAVL(root);
}




void AVLTree::add(Node *T, Node *newNode, Node *parent) {  //��һ�������ǵ�ǰ����ַ�����ݹ��ã��ڶ����������½���ַ
    //AVL���ǿ���ʱ��ͷ�ڵ�ָ�����Ľ��
    if(root == nullptr) {
        root = newNode;
        //��ȡ�������
        depth = getHeight(root);
        sign = true;
        return;
    }


    //AVL��Ϊ��ʱ
    if(T->getUser().username>newNode->getUser().username){  //����ǰ���ֵ���½��ֵ����ת������

        if(T->getLChild() == nullptr){
            T->setLChild(newNode);  //����Ϊ�գ�ֱ�����Ϊ����
            sign = true;
            //��ȡ�������
            depth = getHeight(root);
        } else add(T->getLChild(), newNode, T);  //���ӷǿգ�ת������

    }else if(T->getUser().username<newNode->getUser().username){  //����ǰ���ֵ���½��ֵС����ת���Һ���

        if(T->getRChild() == nullptr){
            T->setRChild(newNode);  //�Һ���Ϊ�գ�ֱ�����Ϊ�Һ���
            sign = true;
            //��ȡ�������
            depth = getHeight(root);
        } else add(T->getRChild(), newNode, T);  //�Һ��ӷǿգ�ת���Һ���

    }else{  //����ǰ���ֵ���½��ֵһ�����򷵻ش�����Ϣ
        cout<<"�û�\""<<newNode->getUser().username<<"\"�Ѵ��ڣ�"<<endl;
        delete newNode;  //�ͷſռ�
        return;
    }

    //ƽ�����
    if(T->getBF() > 1){  //�ҵ���С��ƽ������
        RRotate(T, parent);  //����
    }else if(T->getBF() < -1){
        LRotate(T, parent);  //����
    }
}



/*
 * ���ڻ�ȡ�������ʱ��Ҫ�õ�ÿ������������������
 * ���Կ���˳��������ǰ����ƽ������
 */
int AVLTree::getHeight(Node *T) {  //ʹ�õݹ��ȡ�������
    if(T == nullptr) return 0;

    int left, right;  //��¼�����������

    left = getHeight(T->getLChild());  //��ǰ������������
    right = getHeight(T->getRChild());  //��ǰ������������
    T->setBf(left-right);  //�������ǰ����ƽ������

    return  max(left, right)+1;  //ȡ���������������һ����Ϊ����ֵ
}

void AVLTree::deleteNode(Node *node, string usn, Node *p) {
    if(node == nullptr){
        //cout<<"empty node!"<<endl;
        return;
    }

    if(node->getUser().username == usn){  //����ǰ��㼴Ϊ��Ѱ���

        if(node->getRChild() && node->getLChild()) {//������������ӽ��

            Node* temPreNode = node;  //ָ�������̽���˫�׽��
            Node* temNode = node->getRChild();  //ָ�������̽��
            while(temNode->getLChild() != nullptr){  //�����������������½��
                temPreNode = temNode;
                temNode = temNode->getLChild();
            }

            if(node->getRChild() != temNode){  //�������̽�㲻��Ŀ������Һ���ʱ
                if(temNode->getRChild() != nullptr){  //�������̽ڵ��Һ��Ӳ�Ϊ��
                    temPreNode->setLChild(temNode->getRChild());  //�����̽����Һ��ӱ�Ϊǰһ����������
                }
                temNode->setRChild(node->getRChild());  //��ɾ�������Һ�����Ϊ�����̽ڵ���Һ���
                temPreNode->setLChild(nullptr);  //�����̽���˫�׽�������ÿ�
            }
            temNode->setLChild(node->getLChild());  //��ɾ������������Ϊ�����̽ڵ������

            if(p != nullptr){
                if(p->getRChild() == node) {  //�ǽ����Һ���ʱ
                    p->setRChild(temNode);  //�����̽ڵ���Ϊ˫�׽����Һ���
                }else if(p->getLChild() == node){  //�ǽ�������ʱ
                    p->setLChild(temNode);  //�����̽ڵ���Ϊ˫�׽�������
                }
            }else{
                root = temNode;
            }
            delete node;  //ɾ�������

        } else if(node->getRChild() && !node->getLChild()){  //�����ǰ���ֻ���Һ���

            if(p == nullptr) {  //����Ŀ����Ϊ���ڵ������
                root = node->getRChild();  //���ø��ڵ�
                delete node;  //ɾ�����
            }else if(p->getLChild() == node){  //��Ϊ���ڵ������
                p->setLChild(node->getRChild());
                delete node;  //ɾ�����
            }else if(p->getRChild() == node){  //��Ϊ���ڵ���Һ���
                p->setRChild(node->getRChild());
                delete node;  //ɾ�����
            }

        } else if(!node->getRChild() && node->getLChild()){  //�����ǰ���ֻ������

            if(p == nullptr) {  //����Ŀ����Ϊ���ڵ������
                root = node->getLChild();  //���ø��ڵ�
                delete node;  //ɾ�����
            }else if(p->getLChild() == node){  //��Ϊ���ڵ������
                p->setLChild(node->getLChild());
                delete node;  //ɾ�����
            }else if(p->getRChild() == node){  //��Ϊ���ڵ���Һ���
                p->setRChild(node->getLChild());
                delete node;  //ɾ�����
            }

        } else{  //��ΪҶ�ӽ�㣬��ֱ��ɾ��

            if(p == nullptr){  //���Ŀ��Ϊ�����ĸ��ڵ㣬��ֱ��ɾ��
                delete node;
                root = nullptr;
            }else if(p->getLChild() == node){  //��Ϊ���ڵ������
                delete node;  //ɾ�����
                p->setLChild(nullptr);  //���ڵ�����ָ���ÿ�
            }else if(p->getRChild() == node){  //��Ϊ���ڵ���Һ���
                delete node;  //ɾ�����
                p->setRChild(nullptr);  //���ڵ��Һ���ָ���ÿ�
            }

        }
        node = nullptr;
        //���¼���߶�
        depth = getHeight(root);
        sign = true;
        return;
    }

    deleteNode(node->getLChild(), usn, node);

    //ԭ���λ��ƽ�����
    while(node->getLChild() != nullptr && node->getLChild()->getBF() > 1) {
        RRotate(node, p);  //����
    }

    //����֧ɾ��ʱ���ϲ�ƽ�����
    if(node->getBF() > 1){  //�ҵ���С��ƽ������
        RRotate(node, p);  //����
    }else if(node->getBF() < -1){
        LRotate(node, p);  //����
    }

    deleteNode(node->getRChild(), usn, node);

    //ԭ���λ��ƽ�����
    while(node->getRChild() != nullptr && node->getRChild()->getBF() > 1) {
        RRotate(node, p);  //����
    }

    //����֧ɾ��ʱ���ϲ�ƽ�����
    if(node->getBF() > 1){  //�ҵ���С��ƽ������
        RRotate(node, p);  //����
    }else if(node->getBF() < -1){
        LRotate(node, p);  //����
    }

}

void AVLTree::deleteNode(string usn) {
    deleteNode(root, usn);
}

void AVLTree::RRotate(Node *node, Node *parent) {
    if(node == root){  //����С��ƽ�����������Ϊ���ڵ�
        if(node->getLChild()->getBF() < 0){  //������Ų�ͬ�����ӽ���Ƚ�������
            LRotate(node->getLChild(), node);
        }
        Node *temNode = root;
        root = root->getLChild();

        if(root->getRChild() == nullptr){  //������ӽ��û���Һ���
            root->setRChild(temNode);
            temNode->setLChild(nullptr);
        }else{  //������ӽ�����Һ��ӣ��򽫺��ӽ����Һ����Ƶ�˫�׽������½�
            temNode->setLChild(root->getRChild());
            root->setRChild(temNode);

        }

    } else{  //����Ϊ���ڵ�
        if(node->getLChild()->getBF() < 0){  //������Ų�ͬ�����ӽ���Ƚ�������
            if(parent->getLChild() == node){  //��ߵ�������˫�׽�������
                LRotate(node->getLChild(), parent->getLChild());
            }else{  //�ұߵ�������˫�׽�����ұ�
                LRotate(node->getLChild(), parent->getRChild());
            }
        }

        //��ת����
        Node *temNode = node;
        Node *childNode = node->getLChild();

        if(parent->getLChild() == node){  //��ߵ�����
            parent->setLChild(childNode);
        }else{  //�ұߵ�����
            parent->setRChild(childNode);
        }

        if(childNode->getRChild() == nullptr){  //������ӽ��û���Һ���
            childNode->setRChild(temNode);
            temNode->setLChild(nullptr);
        }else{  //������ӽ�����Һ��ӽ�㣬�򽫺��ӽ����Һ����Ƶ�Ŀ��������½ǣ�������������
            temNode->setLChild(childNode->getRChild());
            childNode->setRChild(temNode);
        }

    }
    depth = getHeight(root);  //���¼���������Ⱥ�bf
}

void AVLTree::LRotate(Node *node, Node *parent) {
    if(node == root){  //����С��ƽ�����������Ϊ���ڵ�
        if (node->getRChild()->getBF() > 0) {  //������Ų�ͬ�����ӽ���Ƚ�������
            RRotate(node->getRChild(), node);
        }
        Node *temNode = root;
        root = root->getRChild();

        if(root->getLChild() == nullptr){  //������ӽ��û������
            root->setLChild(temNode);
            temNode->setRChild(nullptr);
        }else{  //������ӽ�����������ӽ�㣬�򽫺��ӽ��������Ƶ�˫�׽������½�
            temNode->setRChild(root->getLChild());
            root->setLChild(temNode);
        }

    } else {  //����Ϊ���ڵ�
        if (node->getRChild()->getBF() > 0) {  //������Ų�ͬ�����ӽ���Ƚ�������
            if(parent->getLChild() == node){  //��ߵ�������˫�׽�������
                RRotate(node->getRChild(), parent->getLChild());
            }else{  //�ұߵ�������˫�׽�����ұ�
                RRotate(node->getRChild(), parent->getRChild());
            }
        }
        //��ת����
        Node *temNode = node;
        Node *childNode = node->getRChild();

        if(parent->getLChild() == node){  //��ߵ�����
            parent->setLChild(childNode);
        }else{  //�ұ�����
            parent->setRChild(childNode);
        }

        if(childNode->getLChild() == nullptr){  //������ӽ��û������
            childNode->setLChild(temNode);
            temNode->setRChild(nullptr);
        }else{  //������ӽ�����������ӽ�㣬�򽫺��ӽ��������Ƶ�˫�׽������½�
            temNode->setRChild(childNode->getLChild());
            childNode->setLChild(temNode);
        }


    }
    depth = getHeight(root);  //���¼���������Ⱥ�bf
}

void AVLTree::add(string usn, string pwd) {
    add(root, new Node(usn, pwd));
}

void AVLTree::updatePassword(string usn, string pwd, Node *T) {
    if(T == nullptr) return;

    updatePassword(usn, pwd, T->getLChild());

    if(usn == T->getUser().username && pwd == T->getUser().password){
        cout << "        ������:";
        string p;
        cin>>p;
        T->getUser().password = p;
        sign = true;
        return;
    }

    updatePassword(usn, pwd, T->getRChild());
}

void AVLTree::updatePassword(string usn, string pwd) {
    updatePassword(usn, pwd, root);
}

void AVLTree::save(ofstream &outFile) {
    save(outFile,root);
}

void AVLTree::login(string usn, string pwd, Node *T) {
    if(T == nullptr) return;

    login(usn, pwd, T->getLChild());

    if(usn == T->getUser().username && pwd == T->getUser().password){
        sign = true;
    }
    login(usn, pwd, T->getRChild());
}

void AVLTree::login(string usn, string pwd) {
    login(usn, pwd, root);
}

bool AVLTree::getSign() {
    return sign;
}

void AVLTree::reSign() {
    sign = false;
}

void AVLTree::save(ofstream &outFile, Node *T) {
    if(T == nullptr) return;
    if(T == root) outFile<<T->getUser().username<<'@'<<T->getUser().password;
    else outFile<<endl<<T->getUser().username<<'@'<<T->getUser().password;
    save(outFile, T->getLChild());
    save(outFile, T->getRChild());
}


