#include "include.h"

extern const INT8U DefaultKeyABuf[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

data INT8U CardRevBuf[16] = { 0 };

INT8U req_card_sn( INT8U card_sn[] )
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
	
	if( PcdSelect( &CardRevBuf[2] ) != MI_OK )//??
	{
		return FALSE;	
	}
	
	memcpy( &card_sn[0], &CardRevBuf[2], 4 );

	return TRUE;
}
