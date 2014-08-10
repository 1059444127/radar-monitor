/*****************************************************************
	FIFO ʵ��
******************************************************************
*�ļ�����		fifo.c
*����������	        --
*����������	        --
*��˾����		�п�Ժ����΢ϵͳ������
*��ǰ�汾�ţ�	        v1.0
*copyright? 2007, �п�Ժ����΢ϵͳ������ All rights reserved.
*
*����			ʱ��					��ע
*LiPengyu		2009-07-22		��д����Щ����
*����������		�����д�ĵ�ʱ��		��д����Щ����
******************************************************************/
////////////////////////ͷ�ļ����ò���//////////////////////////////



//#include <msp430x14x.h>
#include <stdlib.h>
#include <string.h> 
//#include "mac_inter.h"
#include "fifo.h"
//#include "hal.h"

#ifdef __cplusplus    
extern "C" {
#endif


/****************************************************
*	��������FIFO_LIST* fifo_create(uint8 item_size, uint16 item_cnt)
*	���ߣ�  ��Ʒ������
*	���ʱ�䣺2009-07-16
*	��������˵����
*		����FIFO
*	������
*		uint8 item_size, uint16 item_cnt
*	����ֵ��
*		FIFO_LIST*  FIFO���׵�ַ
*******************************************************/
FIFO_LIST* fifo_create(uint16 item_size, uint16 item_cnt)
{
   FIFO_LIST* phead;
   uint16  size=item_size*item_cnt+sizeof(FIFO_LIST); 
   //uint16* pbuffer=malloc((size+1)/2);
   uint16* pbuffer=malloc(size);
   if(pbuffer==NULL)
   {       
        //debug("SRAMalloc pbuffer error!len %d",size);
         return NULL;
   }
   phead=(FIFO_LIST*)pbuffer;
   phead->head=0; //index of head.
   phead->tail=0; //index of tail.
   phead->item_cnt=0;  //total number of item
   phead->item_max_num=item_cnt;
   phead->item_size=item_size;
   phead->pbuffer=(uint8*)(pbuffer+(sizeof(FIFO_LIST)/2));//buffer of fifo. 
   
   return phead;  
}
/****************************************************
*	��������inline uint16   fifo_next_item(FIFO_LIST* pfifo, uint16 cur_item)
*	���ߣ�  ��Ʒ������
*	���ʱ�䣺2009-07-16
*	��������˵����
*		FIFOָ��Ӽӣ�FIFO�������ݺ�ָ����һ��item
*	������
*		FIFO_LIST* pfifo  ��ǰFIFO
*               uint16 cur_item ��ǰָ��
*	����ֵ��
*		 FIFO�ĵ�ǰָ���ַ
*******************************************************/
uint16   fifo_next_item(FIFO_LIST* pfifo, uint16 cur_item)
{
  cur_item++;
  if(cur_item>=pfifo->item_max_num)
    cur_item=0;
  return cur_item;
}
/****************************************************
*	��������BOOL fifo_set(FIFO_LIST* pfifo, uint8* pitem) 
*	���ߣ�  ��Ʒ������
*	���ʱ�䣺2009-07-16
*	��������˵����
*		�����ݴ���FIFO
*	������
*		FIFO_LIST* pfifo  ��ǰFIFO
*               uint8* pitem  ��ǰFIFOָ��
*	����ֵ��
*		 BOOL FALSE or TRUE �����Ƿ�ɹ�
*******************************************************/
BOOL fifo_set(FIFO_LIST* pfifo, uint8* pitem) 
{
 
	uint8* dst;
  //judge if it is full.
  if(pfifo->item_max_num==(pfifo->item_cnt+1))
  {
	  return FALSE;
  }
  
  dst=pfifo->pbuffer+pfifo->item_size*pfifo->tail;
  //memcpy(dst, pitem, pfifo->item_size);
  memcpy(dst, pitem, 5770);
  
  pfifo->tail=fifo_next_item(pfifo,pfifo->tail);
  pfifo->item_cnt++;

  
  return TRUE;

}
/****************************************************
*	��������BOOL fifo_get(FIFO_LIST* pfifo, uint8* pdest)
*	���ߣ�  ��Ʒ������
*	���ʱ�䣺2009-07-16
*	��������˵����
*		��FIFO�ж�ȡ����
*	������
*		FIFO_LIST* pfifo  ��ǰFIFO
*               uint8* pdest  ��ǰFIFOָ��
*	����ֵ��
*		 BOOL FALSE or TRUE ��ȡ�Ƿ�ɹ�
*******************************************************/
BOOL fifo_get(FIFO_LIST* pfifo, uint8* pdest)
{
   uint8* src;
  //judge if it is empty.
  if(0==pfifo->item_cnt)
    return FALSE;
  
  src=pfifo->pbuffer+pfifo->item_size*pfifo->head;  
  memcpy(pdest, src, pfifo->item_size);
  
  
  pfifo->head=fifo_next_item(pfifo,pfifo->head);
  pfifo->item_cnt--;      
  
   return TRUE;
}
/****************************************************
*	��������uint16 fifo_get_datacnt(FIFO_LIST* pfifo)
*	���ߣ�  ��Ʒ������
*	���ʱ�䣺2009-07-16
*	��������˵����
*		��ȡFIFO�ĳ���
*	������
*		FIFO_LIST* pfifo  ��ǰFIFO
*              
*	����ֵ��
*		uint16  ����
*******************************************************/
uint16 fifo_get_datacnt(FIFO_LIST* pfifo)
{
  return pfifo->item_cnt;
}

BOOL fifo_delete(FIFO_LIST* pfifo)
{
	 free((void *)pfifo);
	return TRUE;
}

#ifdef __cplusplus    // If used by C++ code, 
}          // we need to export the C interface
#endif