#ifndef CDKDISCOVER_H
#define CDKDISCOVER_H

#ifdef __cplusplus
extern "C"	{
#endif

//CDK-S ignore
#include "CDK.h"
/*
//CDK-S end ignore
#include "../include/CDK.h"
//CDK-S ignore
*/
//CDK-S end ignore

	/*! <summary>struct</summary>
	A CDK discover instance represents a UDP socket waiting for Discover packets.
*/
typedef struct _cdkdiscover CDKDiscover;

/*!
	Creates a new instance of CDKDiscover	
	@returns The created CDKDiscover or NULL on failure
*/
CDKDiscover CDK_API * CDKDiscoverCreate();


/*! 
	Deletes a CDKDiscover
	@param[in] pDiscover Pointer to the discover
*/
void CDK_API CDKDiscoverDestroy(CDKDiscover* pDiscover);

/*!
	Starts a discover
	@param[in] pDiscover Pointer to the discover
	@returns CDK_OK on success, or CDK_FAIL in case of error (use <a href="#CDKGetLastError">CDKGetLastError</a> for more details)
*/
int32_t CDK_API CDKDiscoverStart(CDKDiscover* pDiscover);

/*!
	Stops a discover
	@param[in] pDiscover Pointer to the discover
	@returns CDK_OK on success, or CDK_FAIL in case of error (use <a href="#CDKGetLastError">CDKGetLastError</a> for more details)
*/
int32_t CDK_API CDKDiscoverStop(CDKDiscover* pDiscover);

/*!
	gets the discovered equipments. If ppMsg is NULL, puCount is filled with the number of discovered equipments. Otherwise, ppMsg is filled with CDKMsg. There CDKMsg have to be destroyed by the application.
	@param[in] pDiscover Pointer to the discover
	@param[in] ppMsg pointer to an array of CDKMsg*, or NULL
	@param[in] puCount pointer to the size of the array
	@returns CDK_OK on success, or CDK_FAIL in case of error (use <a href="#CDKGetLastError">CDKGetLastError</a> for more details)
*/
int32_t CDK_API CDKDiscoverGetDiscovered(CDKDiscover* pDiscover, CDKMsg** ppMsg, uint32_t* puCount);

#ifdef __cplusplus
}
#endif

#endif //CDKDISCOVER_H
