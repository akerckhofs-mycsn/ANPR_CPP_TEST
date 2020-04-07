/*! \file

CDKSignature : Signature management, for comparing signatures

*/

#ifndef CDKSIGNATURE_H
#define CDKSIGNATURE_H

#ifdef __cplusplus
extern "C"	{
#endif

/*! <summary>struct</summary>
	a CDKSignature contains the signature for one vehicle
*/
typedef struct _cdksignature CDKSignature;

/*!
	Creates a CDKSignature instance from binary buffer. Use <a href="#CDKSignatureDestroy">CDKSignatureDestroy</a> to destroy it.
	@param[in] pBuffer binary buffer
	@param[in] uSize binary buffer size
	@returns the created CDKSignature instance or NULL if there was an error
*/
CDKSignature CDK_API * CDKSignatureCreate(const uint8_t* pBuffer, uint32_t uSize);

/*!
	Destroys a CDKSignature instance
*/
void CDK_API CDKSignatureDestroy(CDKSignature* pSignature);

/*!
	Compares 2 signatures.
	@param[in] pSignature1 The first signature to compare
	@param[in] pSignature2 The second signature to compare
	@returns The comparison score, between 0 and 10, 10 is the best, or -1 in case of error. In cas of error, you can get the error text by calling <a href="#CDKGetLastError">CDKGetLastError</a> with pSignature1
*/
int32_t CDK_API CDKSignatureCompare(CDKSignature* pSignature1, CDKSignature* pSignature2);

/*!
	Compares 2 signatures with a minimum score. This is an optimized version of CDKSignatureCompare
	@param[in] pSignature1 The first signature to compare
	@param[in] pSignature2 The second signature to compare
	@returns The comparison score, between 0 and 10, 10 is the best, or -1 in case of error. In cas of error, you can get the error text by calling <a href="#CDKGetLastError">CDKGetLastError</a> with pSignature1
*/
int32_t CDK_API CDKSignatureCompareEx(CDKSignature* pSignature1, CDKSignature* pSignature2, int32_t iMinScoreRequired);


#ifdef __cplusplus
}
#endif

#endif //CDKSIGNATURE_H