#include "include.h"

sbit BEEP = P1^7;
sbit KEY = P3^3;
sbit LED = P3^5;
sbit LOCK = P1^0;
unsigned char card_sn[4] = { 0 };//���������ݴ�

int n; //��������
int addMode=FALSE;  //���ģʽ


//��ʱN����
void delayms(unsigned char n)		//@32.000MHz
{
	unsigned char i, j;

	i = 32;
	j = 29;
	do{
		do {
			while (--j);
		} while (--i);
	} while(--n);
}

//��N��
void beepTime(int n){
	unsigned char d = 100 / (2*n);
	do {
		BEEP=0;
		delayms(d);
		BEEP=1;
		delayms(d);
	} while(--n);
}

//���Ƽ̵�������
void openDoor(void){
	LOCK=0;
	delayms(100);
	LOCK=1;
}

//��֤
int auth(){
	int i,j;
	
	n=IapReadByte(0x0000); //��ȡ���ݿ����еĿ���Ŀ
	
	for (j=0;j<=n;j++){
		for (i=0;i<4;i++){
			if(card_sn[i] != IapReadByte((j*0x0200)+i)) //��ȡ����
				break;
			else if(i == 3) return 1;
		}
	}
	return 0;
}

//��ӿ�
void addKey(){
	int i;
	
	n=IapReadByte(0x0000);				//��ȡ���ݿ����еĿ���Ŀ
	
	IapEraseSector((n+1)*0x0200);	//��յ�N+1��
	for (i=0;i<4;i++){
			IapProgramByte((n+1)*0x0200+i,card_sn[i]);  //д������
	}
	
	IapEraseSector(0x0000);       //�����Ŀ��
	IapProgramByte(0x0000,++n);   //д���µ���Ŀ
	addMode=FALSE;
	beepTime(2);
}

void main(void){
	
	init_rc522();
	
	while(1){
		if(req_card_sn(card_sn)){
			if( auth() ){ 		//�жϿ��Ƿ������ݿ���
				if(!addMode){		//ͨ��ģʽ
					beepTime(1);	//��һ��
					openDoor();		//����
				} else {        //���Ѿ������ݿ���
					beepTime(3); 	//������
					addMode=FALSE;//�˳�
				}
			} else {
				if(!addMode)
					beepTime(2);  //���Ŵ���
				else addKey();  //��ӿ�
			}
		}
		if(!KEY){
			addMode=TRUE;
			BEEP=0;
		}
	}
}