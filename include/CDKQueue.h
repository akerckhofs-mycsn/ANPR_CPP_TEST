/*! \file

CDKQueue : message queue.

*/

#ifndef CDKQUEUE_H
#define CDKQUEUE_H

#ifdef __cplusplus
extern "C"	{
#endif

/*! <summary>struct</summary>

    A queue
*/
typedef struct _CDKQueue CDKQueue;

#include "CDKMsg.h"

/*! <summary>callback</summary>

    Callback called when there is something to be read in the queue. Note that you should not pop messages inside this callback.<br/>
	This callback is defined with the fuction <a href="CDKQueueSetNewMessageCallback">CDKQueueSetNewMessageCallback</a>.
	@param[in] pCDK Pointer to the CDKQueue that has a new message in its queue
	@param[in] pUser User data
*/
typedef void (*PCDKQUEUENEWMESSAGECALLBACK) (CDKQueue* pQueue, void* pUser);

/*!
	Creates a CDK queue instance. Use <a href="#CDKQueueDestroy">CDKQueueDestroy</a> to destroy it.
	@returns the created CDK queue instance or NULL if there was an error
*/
CDKQueue CDK_API * CDKQueueCreate();

/*!
	Destroys a CDK queue instance. Note that a queue cannot be destroyed if a CDK instance uses it.
	@param[in] pQueue CDK Queue instance
	@returns true if the queue has been destroyed, false if it can't be destroyed.
*/
int32_t CDK_API CDKQueueDestroy(CDKQueue* pQueue);

/*!
	Sets the <a href="#PCDKQUEUENEWMESSAGECALLBACK">new message callback</a>.
	@param[in] pQueue CDK Queue instance
	@param[in] newMessageCallback a pointer to the callback function
	@param[in] pUser callback user data
*/
void CDK_API CDKQueueSetNewMessageCallback(CDKQueue* pQueue, PCDKQUEUENEWMESSAGECALLBACK newMessageCallback, void* pUser);

/*!
	Returns the number of messages dropped since the last <a href="#CDKResetMessageDrops">CDKResetMessageDrops</a>.<br/>
	It is recommended to regularly check messages drops.
	@param[in] pQueue CDK Queue instance
	@returns the number of messages dropped
*/
uint32_t CDK_API CDKQueueGetMessageDrops(CDKQueue* pQueue);

/*!
	Resets the count of message drops.
	@param[in] pQueue CDK Queue instance
*/
void CDK_API CDKQueueResetMessageDrops(CDKQueue* pQueue);

/*!
	Returns the maximum queue size. If a message is received while the queue is full, it will be dropped.
	@param[in] pQueue CDK Queue instance
	@returns the maximum queue size
*/
uint32_t CDK_API CDKQueueGetMaxQueueSize(CDKQueue* pQueue);
/*!
	Changes the maximum queue size. Default value is 128.
	@param[in] pQueue CDK Queue instance
	@param[in] uMax the new maximum queue size
*/
void CDK_API CDKQueueSetMaxQueueSize(CDKQueue* pQueue, uint32_t uMax);

/*!
	Blocks until a new message is received in the queue, or the timeout is reached.
	@param[in] pCDK CDK instance
	@param[in] uTimeout the timeout in ms
	@returns CDK_OK if there is a new message, or CDK_FAIL if the timeout has been reached.
*/
int32_t CDK_API CDKQueueWaitForNewMessage(CDKQueue* pQueue, uint32_t uTimeout);

/*!
	Returns the current size of the queue : the number of messages received, to be read by the application.
	@param[in] pQueue CDK Queue instance
	@returns the queue size
*/
uint32_t CDK_API CDKQueueGetQueueSize(CDKQueue* pQueue); 

/*!
	Adds a message to the queue. The message is then owned by the queue and must not be destroyed by the application.<br/>
	Note that if the message could not be push, it is NOT owned by the queue, and then must be destroyed by the application
	@param[in] pQueue CDK Queue instance
	@param[in] pMsg the message to queue
	@returns CDK_OK on success. CDK_FAIL if the queue is full
*/
int32_t CDK_API CDKQueuePushMessage(CDKQueue* pQueue, CDKMsg* pMsg);

/*!
	Takes the oldest message from the queue. The message is then owned by the application and has to be destroyed by it.
	@param[in] pQueue CDK Queue instance
	@returns the message taken or NULL if there is no message in the queue.
*/
CDKMsg CDK_API * CDKQueuePopMessage(CDKQueue* pQueue);

#ifdef __cplusplus
}
#endif

#endif //CDKQUEUE_H