#include "include.h"

data unsigned char CardRevBuf[16] = { 0 };

unsigned char req_card_sn( unsigned char card_sn[] )
{
	if( PcdRequest( PICC_REQIDL, &CardRevBuf[0] ) != MI_OK )//Ѱ��������δ��������״̬�Ŀ������ؿ�Ƭ���� 2�ֽ�	
	{
		if( PcdRequest( PICC_REQIDL, &CardRevBuf[0] ) != MI_OK )//Ѱ��������δ��������״̬�Ŀ������ؿ�Ƭ���� 2�ֽ�	
		{
			return FALSE;
		}	
	}
	
	if( PcdAnticoll( &CardRevBuf[2] ) != MI_OK ) //����ײ�����ؿ������к� 4�ֽ� 
	{
		return FALSE;	
	}
	memcpy( &card_sn[0], &CardRevBuf[2], 4 );

	return TRUE;
}
