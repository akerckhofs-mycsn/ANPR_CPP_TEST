/*! \file

CDK : a CDK instance represents a link to a SURVISION equipment.

*/

#ifndef CDK_H
#define CDK_H

#ifdef __cplusplus
extern "C"	{
#endif

#ifndef CDK_API
#define CDK_API
#endif

/*!
	Returned by succesful functions
*/
#define CDK_OK 1
/*!
	Returned by failed functions
*/
#define CDK_FAIL 0

/*! <summary>struct</summary>
	A CDK instance represents a link with a SURVISION equipment.
*/
typedef struct _cdk CDK;

/*!
	Unable to access on the certificate revocation list
*/
#define CDK_ERR_UNABLE_TO_GET_CRL			0x01
/*!
	The sensor certificate is not yet valid
*/
#define CDK_ERR_CERT_NOT_YET_VALID			0x02
/*!
	The sensor certificate is no longer valid
*/
#define CDK_ERR_CERT_HAS_EXPIRED			0x04
/*!
	One of the sensor certificate in certification chain is self-signed
*/
#define CDK_ERR_SELF_SIGNED_CERT_IN_CHAIN	0x08
/*!
	The sensor certificate chain is too long (set as 3)
*/
#define CDK_ERR_CERT_CHAIN_TOO_LONG			0x10
/*!
	One of the sensor certificate in chain is revoked by a Certificate Revocation List
*/
#define CDK_ERR_CERT_REVOKED				0x20
/*!
	The sensor certificate autority is not trusted
*/
#define CDK_ERR_INVALID_CA					0x40

#include "CDKMsg.h"
#include "CDKQueue.h"

/*! <summary>callback</summary>

    Callback called when CDK needs to write a trace.<br/>
	This callback is defined with the fuction <a href="#CDKSetTraceFunction">CDKSetTraceFunction</a>.
	@param[in] pCDK Pointer to the CDK that sent the trace. Note that it can be NULL
	@param[in] level trace level : 1 (CRITICAL) to 8 (DEBUG)
	@param[in] strTrace trace text
	@param[in] pUser User data
*/
typedef void (*PCDKTRACEFUNCTION)(CDK* pCDK, uint8_t level, const char* strTrace, void* pUser);

/*!
	Static function that sets the <a href="#PCDKTRACEFUNCTION">trace callback</a>.<br/>
	It is highly recommended to set the trace callback on application startup.
	@param[in] traceFunction a pointer to the callback function
	@param[in] pUser callback user data
*/
void CDK_API CDKSetTraceFunction(PCDKTRACEFUNCTION traceFunction, void* pUser);

/*!
	Returns the object's last error
	@param[in] pCDKObject the object : can be a <a href="#CDK">CDK</a> instance, or any other class of the CDK.
	@returns the error in ASCII
*/
const char CDK_API * CDKGetLastError(void* pCDKObject);


/*!
	Returns the current CDK version
	@returns the CDK version as an ASCII string
*/
const char CDK_API * CDKGetVersion();

/*!
	Fills the string strVersion with all version informations (CDK and its dependencies)
	@param[in] strVersion the string
*/
void CDK_API CDKGetFullVersion(char* strVersion);



/*! <summary>callback</summary>

	This callback is deprecated, please use <a href="#PCDKSTATECALLBACK2">PCDKSTATECALLBACK2</a>.<br/>
    Callback called when CDK connection state changes.<br/>
	This callback is defined with the fuction <a href="#CDKSetConnectionStateCallback">CDKSetConnectionStateCallback</a>.
	@param[in] pCDK Pointer to the CDK that changes state
	@param[in] bConnected 1 if the CDK is connected to the linked equipment
	@param[in] pUser User data
*/
typedef void (*PCDKSTATECALLBACK)(CDK* pCDK, int32_t bConnected, void* pUser);

/*! <summary>callback</summary>

Callback called when CDK connection state changes.<br/>
This callback is defined with the fuction <a href="#CDKSetConnectionStateCallback2">CDKSetConnectionStateCallback2</a>.
@param[in] pCDK Pointer to the CDK that changes state
@param[in] bConnected 1 if the CDK is connected to the linked equipment
@param[in] u32SSLErrors list of SSL errors (OR of <a href="#CDK_ERR_UNABLE_TO_GET_CRL (0x01)">these defines</a>)
@param[in] pUser User data
*/
typedef void(*PCDKSTATECALLBACK2)(CDK* pCDK, int32_t bConnected, uint32_t u32SSLErrors, void* pUser);


/*! <summary>callback</summary>

    Callback called when a new message is pushed to the queue and there is nothing in the queue before adding this new message. <br/>
	Note that there can be already messages in the queue, in which case the callback is not called.<br/>
	Note also that you should not pop messages inside this callback.<br/>
	This callback is defined with the function <a href="#CDKSetNewMessageCallback">CDKSetNewMessageCallback</a>.
	@param[in] pCDK Pointer to the CDK that has a new message in its queue
	@param[in] pUser User data
*/
typedef void (*PCDKNEWMESSAGECALLBACK) (CDK* pCDK, void* pUser);

/*!
	Creates a CDK instance. Use <a href="#CDKDestroy">CDKDestroy</a> to destroy it.
	@returns the created CDK instance or NULL if there was an error
*/
CDK CDK_API * CDKCreate();

/*!
	Destroys a CDK instance
*/
void CDK_API CDKDestroy(CDK* pCDK);

/*!
	Binds a CDK instance to a SURVISION equipment.<br/>
	
	@param[in] pCDK CDK instance
	@param[in] strAddress equipment IPv4 address or hostname
	@param[in] uPort equipment port. Default value is 10001.
	@param[in] options <a href="#Bind options">options</a>
			
	@returns CDK_OK on success. In case of failure, use <a href="#CDKGetLastError">CDKGetLastError</a> for more details
*/
int32_t CDK_API CDKBind(CDK* pCDK, const char* strAddress, uint16_t uPort, const char* options);

/*!
Binds a CDK SSL instance to a SURVISION equipment.<br/>

@param[in] pCDK CDK instance
@param[in] strAddress equipment IPv4 address or hostname
@param[in] uPort equipment port. Default value is 12001.
@param[in] options <a href="#Bind options">options</a>

@returns CDK_OK on success. In case of failure, use <a href="#CDKGetLastError">CDKGetLastError</a> for more details
*/
int32_t CDK_API CDKBindS(CDK* pCDK, const char* strAddress, uint16_t uPort, const char* options);

/*!
	Unbinds a CDK instance to a SURVISION equipment. Note that <a href="#CDKDestroy">CDKDestroy</a> automatically unbinds the equipment.
	@param[in] pCDK CDK instance
	@returns CDK_OK on success. In case of failure, use <a href="#CDKGetLastError">CDKGetLastError</a> for more details
*/
int32_t CDK_API CDKUnbind(CDK* pCDK);

/*!
	Returns the server IP address binded
	@param[in] pCDK CDK instance
	@returns the server address
*/
const char CDK_API * CDKGetAddress(CDK* pCDK);

/*!
	Returns the server port
	@param[in] pCDK CDK instance
	@returns the server port
*/
uint16_t CDK_API CDKGetPort(CDK* pCDK);

/*!
	Sets a queue for the CDK to use. The queue must have been created with <a href="CDKQueueCreate">CDKQueueCreate</a>.<br/>
	Note that, by default, the CDK uses its own internal queue.
	@param[in] pCDK CDK instance
	@param[in] pQueue The CDKQueue instance to use
*/
void CDK_API CDKSetQueue(CDK* pCDK, CDKQueue* pQueue);

/*!
	Returns the CDK connection state to its linked equipment
	@returns 1 if connected
*/
int32_t CDK_API CDKGetConnectionState(CDK* pCDK);

/*!
	This function is deprecated, please use <a href="#CDKSetConnectionStateCallback">CDKSetConnectionStateCallback2</a>.<br/>
	Sets the <a href="#PCDKSTATECALLBACK">connection state callback</a>.
	@param[in] pCDK CDK instance
	@param[in] stateCallback a pointer to the callback function
	@param[in] pUser callback user data
*/
void CDK_API CDKSetConnectionStateCallback(CDK* pCDK, PCDKSTATECALLBACK stateCallback, void* pUser);

/*!
Sets the <a href="#PCDKSTATECALLBACK2">connection state callback</a>.
@param[in] pCDK CDK instance
@param[in] stateCallback a pointer to the callback function
@param[in] pUser callback user data
*/
void CDK_API CDKSetConnectionStateCallback2(CDK* pCDK, PCDKSTATECALLBACK2 stateCallback, void* pUser);

/*!
	Sets the <a href="#PCDKNEWMESSAGECALLBACK">new message callback</a>.
	@param[in] pCDK CDK instance
	@param[in] newMessageCallback a pointer to the callback function
	@param[in] pUser callback user data
*/
void CDK_API CDKSetNewMessageCallback(CDK* pCDK, PCDKNEWMESSAGECALLBACK newMessageCallback, void* pUser);

/*!
	Returns the number of messages dropped since the last <a href="#CDKResetMessageDrops">CDKResetMessageDrops</a>.<br/>
	It is recommended to regulary check messages drops.
	@param[in] pCDK CDK instance
	@returns the number of messages dropped
*/
uint32_t CDK_API CDKGetMessageDrops(CDK* pCDK);

/*!
	Resets the count of message drops.
	@param[in] pCDK CDK instance
*/
void CDK_API CDKResetMessageDrops(CDK* pCDK);

/*!
	Returns the maximum queue size. If a message is received while the queue is full, it will be dropped.
	@param[in] pCDK CDK instance
	@returns the maximum queue size
*/
uint32_t CDK_API CDKGetMaxQueueSize(CDK* pCDK);

/*!
	Changes the maximum queue size. Default value is 128. You should not have to change this value.
	@param[in] pCDK CDK instance
	@param[in] uMax the new maximum queue size
*/
void CDK_API CDKSetMaxQueueSize(CDK* pCDK, uint32_t uMax);

/*!
	Blocks until a new message is received in the queue, or the timeout is reached.
	@param[in] pCDK CDK instance
	@param[in] uTimeout the timeout in ms
	@returns CDK_OK if there is a new message, or CDK_FAIL if the timeout has been reached.
*/
int32_t CDK_API CDKWaitForNewMessage(CDK* pCDK, uint32_t uTimeout);

/*!
	Returns the current size of the queue : the number of messages received, to be read by the application.
	@param[in] pCDK CDK instance
	@returns the queue size
*/
uint32_t CDK_API CDKGetQueueSize(CDK* pCDK);

/*!
	Takes the oldest message from the queue. The message is then owned by the application and has to be destroyed by it.
	@param[in] pCDK CDK instance
	@returns the message taken (has to be destroyed by the application) or NULL if there is no message in the queue.
*/
CDKMsg CDK_API * CDKPopMessage(CDK* pCDK);

/*!
	Sends a message to the equipment and waits for an answer, on the synchronous connection. If the equipment is not connected at the time of the request, this function will returns NULL.<br/>
	The sent message must be destroyed by the application.
	@param[in] pCDK CDK instance
	@param[in] pMsgToSend the message to be sent (has to be destroyed by the application)
	@param[in] uTimeoutMs timeout for the request, in milliseconds
	@returns the answered message (has to be destroyed by the application), or NULL in case of error (use <a href="#CDKGetLastError">CDKGetLastError</a> for more details)
*/
CDKMsg CDK_API * CDKSendRequest(CDK* pCDK, CDKMsg* pMsgToSend, uint32_t uTimeoutMs);

/*!
	Sends a message to the equipment on the asynchronous connection.<br/>
	The sent message must be destroyed by the application.
	@param[in] pCDK CDK instance
	@param[in] pMsgToSend the message to be sent (has to be destroyed by the application)
	@returns CDK_OK on success, or CDK_FAIL in case of error (use <a href="#CDKGetLastError">CDKGetLastError</a> for more details)
*/
int32_t CDK_API CDKSendAsynchronousMessage(CDK* pCDK, CDKMsg* pMsgToSend);

/*!
	Waits until the CDK is connected to the binded equipment, or the timeout is reached.
	@param[in] pCDK CDK instance
	@param[in] uTimeout timeout (in ms)
	@returns CDK_OK if the connection has been established, or CDK_FAIL, if the timeout has been reached.
*/
int32_t CDK_API CDKWaitForConnection(CDK* pCDK, uint32_t uTimeout);

/*!
	Returns the detected protocol of the server.
	@param[in] pCDK CDK instance
	@returns the detected protocol : NPP or CLP
*/
const char CDK_API *CDKGetDetectedProtocol(CDK* pCDK);


/*!
Returns 1 if the CDK is binded in secured mode
@param[in] pCDK CDK instance
@returns 1 if the CDK is binded in secured mode 
*/
uint32_t CDK_API CDKGetSSL(CDK* pCDK);

/*!
Sets the list of SSL errors to be ignored. Use 0xFFFFFFFF to ignore all errors
@param[in] pCDK CDK instance
@param[in] uErrors List of SSL errors ( OR on CDK_ERR_x, see  <a href="#CDK_ERR_UNABLE_TO_GET_CRL (0x01)">these defines</a> )  
*/
void CDK_API CDKSetIgnoreSSLErrors(CDK* pCDK, uint32_t uErrors);

/*!
Returns the list of ignored SSL errors ( OR on CDK_ERR_x, see  <a href="#CDK_ERR_UNABLE_TO_GET_CRL (0x01)">these defines</a> )  
@param[in] pCDK CDK instance
@returns the list of ignored SSL errors
*/
uint32_t CDK_API CDKGetIgnoreSSLErrors(CDK* pCDK);

/*!
Returns the list of SSL errors ( OR on CDK_ERR_x, see  <a href="#CDK_ERR_UNABLE_TO_GET_CRL (0x01)">these defines</a> )  
@param[in] pCDK CDK instance
*/
uint32_t CDK_API CDKGetSSLErrors(CDK* pCDK);


#ifdef __cplusplus
}
#endif

#endif //CDK_H
