#include "AVLTree.h"
int main() {
    ifstream inFile;
    ofstream outFile;
    int num = -1, num2 = -1;
    string name, pwd;

    inFile.open("test.txt",ios::in);
    outFile.open("test1.txt");
    AVLTree test(inFile);  //��ȡ����

    while(true){
        system("cls");
        cout << "--------�û���¼ϵͳ--------\n\n";
        cout << "        1:�û���¼\n";
        cout << "        0:�˳�\n\n";
        cout << "----------------------------\n\n";
        cout << "        ����������ѡ��:";
        cin >> num;
        switch (num)
        {
            case 0:
                break;
            case 1:
            {
                system("cls");
                cout << "----------��¼----------\n\n";
                cout << "        �û�����";
                cin >> name;
                cout << "\n        ���룺";
                cin >> pwd;
                test.login(name, pwd);
                if (test.getSign())
                {
                    test.reSign();
                    while (1)
                    {
                        system("cls");
                        cout << "--------��¼�ɹ�!---------\n\n";
                        cout << "        1:�û��������\n";
                        cout << "        2:�û����\n";
                        cout << "        3:�û�ɾ��\n";
                        cout << "        4:��ʾ��ǰ��\n";
                        cout << "        0:�˳�\n\n";
                        cout << "--------------------------\n\n";
                        cout << "        ����������ѡ��:";
                        cin >> num2;
                        switch (num2)
                        {
                            case 0:
                                break;
                            case 1:
                            {
                                system("cls");
                                cout << "--------�û��������--------\n\n";
                                test.updatePassword(name, pwd);
                                if (test.getSign())
                                {
                                    test.reSign();
                                    cout << "\n        �����޸ĳɹ�!\n";
                                    cout << "--------------------------\n\n";
                                }
                                system("pause");
                                break;
                            }
                            case 2:
                            {
                                system("cls");
                                string nName, nPwd;
                                cout << "--------�û����ǰ--------\n";
                                test.print();
                                cout << "--------------------------\n\n";
                                cout << "---------�û����---------\n\n";
                                cout << "         �û�����";
                                cin >> nName;
                                cout << "\n         ���룺";
                                cin >> nPwd;
                                test.add(nName, nPwd);
                                if (test.getSign())
                                {
                                    test.reSign();
                                    cout << "\n        �û���ӳɹ�!\n";
                                    cout << "--------------------------\n\n";
                                    cout << "--------�û���Ӻ�--------\n";
                                    test.print();
                                    cout << "--------------------------\n\n";
                                }
                                system("pause");
                                break;
                            }
                            case 3:
                            {
                                system("cls");
                                string dName;
                                cout << "--------�û�ɾ��ǰ--------\n";
                                test.print();
                                cout << "--------------------------\n\n";
                                cout << "---------�û�ɾ��---------\n\n";
                                cout << "        ɾ�����û���:";
                                cin >> dName;
                                test.deleteNode(dName);
                                if (test.getSign()) {
                                    test.reSign();
                                    cout << "\n        �û�ɾ���ɹ�!\n\n";
                                    cout << "--------�û�ɾ����--------\n";
                                    test.print();
                                    cout << "--------------------------\n\n";
                                }
                                else
                                {
                                    cout << "\n        �û�ɾ��ʧ��!\n\n";
                                }
                                system("pause");
                                break;
                            }
                            case 4:
                                system("cls");
                                test.print();
                                system("pause");
                                break;
                            default:
                                break;
                        }
                        if (num2 == 0)
                        {
                            system("cls");
                            break;
                        }
                    }
                }
                else
                {
                    cout << "\n     �û������������!\n\n";
                    system("pause");
                }
                break;
            }
            default:
                break;
        }
        if (num == 0)break;
    }
    test.save(outFile);  //��������
    outFile.close();
    inFile.close();
    return 0;
}
