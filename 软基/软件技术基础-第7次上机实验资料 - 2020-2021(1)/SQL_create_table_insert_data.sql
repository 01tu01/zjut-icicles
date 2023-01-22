USE JXGL7
GO

create table SS
(
SCODE# char(10) primary key,
SSNAME nchar(10)
);

insert into SS values('S0401', '�������ѧ�뼼��');
insert into SS values('S0402', 'ָ���Զ���');
insert into SS values('S0403', '���繤��');
insert into SS values('S0404', '��Ϣ�о��밲ȫ');

create table C 
(
    C# char(10) PRIMARY KEY,
    CNAME nchar(10),
    CLASSH tinyint
);

insert into C values ('C401001', '���ݽṹ', 70);
insert into C values ('C401002', '����ϵͳ', 60);
insert into C values ('C402001', '�����ԭ��', 60);
insert into C values ('C402002', 'ͨ��ԭ��', 60);
insert into C values ('C403001', '���������', 60);
insert into C values ('C403002', '��Ϣ��ȫ����', 50);
insert into C values ('C404001', '��Ϣ���������', 60);



create table S 
(
    S# char(10) PRIMARY KEY,
    SNAME nchar(10) NOT NULL,
    SSEX nchar(1) check(SSEX IN ('��','Ů')) NOT NULL,
    SBIRTHIN datetime,
    PLACEOFB nchar(20),
    SCODE# char(10) NOT NULL,
    CLASS nchar(10) NOT NULL,
    foreign key (SCODE#) references SS(SCODE#)
);


insert into S values ('200401001', '�Ż�', '��', '1982-11-14', '����', 'S0401', '200401');
insert into S values ('200401002', '�ƽ', '��', '1982-8-20', '�Ϻ�', 'S0401', '200401');
insert into S values ('200401003', '������', 'Ů', '1982-2-2', '�Ϻ�', 'S0401', '200401');
insert into S values ('200402001', '�����', 'Ů', '1983-5-9', '����', 'S0402', '200402');
insert into S values ('200402002', '��־ΰ', '��', '1982-6-30', '�Ͼ�', 'S0402', '200402');
insert into S values ('200402003', '����', '��', '1983-6-25', '����', 'S0402', '200402');
insert into S values ('200403001', '������', 'Ů', '1982-3-11', '��ɳ', 'S0403', '200403');


create table SC 
(
    S# char(10),
    C# char(10),
    GRADE smallint CHECK(GRADE BETWEEN 0 AND 100),
    PRIMARY KEY(S#,C#),
    foreign key (S#) references S(S#),
    foreign key (C#) references C(C#)
);

insert into SC values ('200401001', 'C401001', 90);
insert into SC values ('200401001', 'C402002', 90);
insert into SC values ('200401001', 'C403001', null);
insert into SC values ('200401002', 'C401001', 75);
insert into SC values ('200401002', 'C402002', 88);
insert into SC values ('200401003', 'C402002', 69);
insert into SC values ('200402001', 'C401001', 87);
insert into SC values ('200402001', 'C401002', 90);
insert into SC values ('200402002', 'C403001', 92);
insert into SC values ('200402003', 'C403001', 83);
insert into SC values ('200403001', 'C403002', 91);

create table T (T# char(10) primary key, 
                TNAME nchar(5) not null, 
                TSEX nchar(1) check(TSEX IN ('��','Ů')), 
                TBIRTHIN datetime not null, 
                TITLEOF nchar(5), 
                TRSECTION nchar(10) not null, 
                TEL char(16));
                
insert into T values('T0401001','�Ź���','��','1950-5-1','����','�����','8810801');
insert into T values('T0401002','���','��','1977-6-22','��ʦ','�����','8899202');
insert into T values('T0402001','������','Ů','1962-8-30','����','ָ���Զ���','8851803');
insert into T values('T0402002','������','Ů','1968-12-11','������','ָ���Զ���','8882604');
insert into T values('T0403001','����ΰ','��','1959-11-29','������','���繤��','8815805');
insert into T values('T0403002','�θ�','Ů','1982-3-15',null,'���繤��',null);

create table TEACH
(
T# char(10),
C# char(10),
primary key(T#, C#),
foreign key (T#) references T(T#),
foreign key (C#) references C(C#)
);

insert into TEACH values('T0401001', 'C401002');
insert into TEACH values('T0401002', 'C401001');
insert into TEACH values('T0402001', 'C402001');
insert into TEACH values('T0402002', 'C402002');
insert into TEACH values('T0403002', 'C403001');



select top 3 * from S;
select top 3 * from C;
select top 3 * from SC;
select top 3 * from T;
select top 3 * from SS;