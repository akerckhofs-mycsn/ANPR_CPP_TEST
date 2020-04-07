#pragma once
/*! \file

CDKPlateFingerprintMatcher

*/

#ifndef CDKPLATEFINGERPRINTMATCHER_H
#define CDKPLATEFINGERPRINTMATCHER_H

#ifdef __cplusplus
extern "C"	{
#endif

#ifndef CDK_API
#define CDK_API
#endif

/*! <summary>struct</summary>
	The CDKPlateFingerprintMatcher is used for comparing 2 fingerprints and know if they describe the same plate.
*/
typedef struct _cdkplatefingerprintmatcher CDKPlateFingerprintMatcher;

/*! <summary>callback</summary>

	Callback called when a CDKPlateFingerprintMatcher needs to write a trace.<br/>
	This callback is defined with the fuction <a href="#CDKPlateFingerprintMatcherSetTraceFunction">CDKPlateFingerprintMatcherSetTraceFunction</a>.
	@param[in] pMatcher Pointer to the matcher that sent the trace. Note that it can be NULL
	@param[in] level trace level : 1 (CRITICAL) to 8 (DEBUG)
	@param[in] strTrace trace text
	@param[in] pUser User data
*/
typedef void (*PCDKPLATEFINGERPRINTMATCHERTRACEFUNCTION)(CDKPlateFingerprintMatcher* pMatcher, uint8_t level, const char* strTrace, void* pUser);

/*! <summary>callback</summary>

	Callback called when a CDKPlateFingerprintMatcher needs to save its dictionary. The application should save the dictionary wherever it wants, and reuse the saved dictionary at next startup with <a href="#CDKPlateFingerprintMatcherSetDictionary">CDKPlateFingerprintMatcherSetDictionary</a><br/>
	If the dictionary is not saved and reused at next startup, the learning phase will begin at each Matcher startup.<br/>
	This callback is defined with the fuction <a href="#CDKPlateFingerprintMatcherSetSaveDictionaryCallback">CDKPlateFingerprintMatcherSetSaveDictionaryCallback</a>.
	@param[in] pMatcher Pointer to the matcher that needs to save its dictionary
	@param[in] binary data containing the dictionary. Note that the dictionary is not very big (a few bytes)
	@param[in] uSize size of binary data
	@param[in] pUser User data
	@returns the callback must return 1 on success, and 0 on failure
*/
typedef int32_t (*PCDKPLATEFINGERPRINTMATCHERSAVEDICTIONARYFUNCTION)(CDKPlateFingerprintMatcher* pMatcher, const uint8_t* pBuffer, uint32_t uSize, void* pUser);

/*!
	Static function that sets the <a href="#PCDKPLATEFINGERPRINTMATCHERTRACEFUNCTION">trace callback</a>.<br/>
	It is highly recommended to set the trace callback on application startup.
	@param[in] traceFunction a pointer to the callback function
	@param[in] pUser callback user data
*/
void CDK_API CDKPlateFingerprintMatcherSetTraceFunction(PCDKPLATEFINGERPRINTMATCHERTRACEFUNCTION traceFunction, void* pUser);
	
/*!
	Creates a CDKPlateFingerprintMatcher
	@returns a new matcher
*/
CDKPlateFingerprintMatcher CDK_API * CDKPlateFingerprintMatcherCreate();
/*!
	Destroys a CDKPlateFingerprintMatcher
	@param[in] pMatcher the matcher to destroy
*/
void CDK_API CDKPlateFingerprintMatcherDestroy(CDKPlateFingerprintMatcher* pMatcher);

/*!
	Sets the dictionary for the matcher. If no dictionary is set, the plateFingerprint algorithm will begin a learning phase, during which comparison results may be not optimal.<br/>
	The dictionary must be saved with the <a href="#PCDKPLATEFINGERPRINTMATCHERSAVEDICTIONARYFUNCTION">save Dictionary callback</a>.
	@param[in] pMatcher the matcher
	@param[in] pBuffer binary data containing the dictionary
	@param[in] uSize size of binary data
	@returns 1 on success. Note that the dictionary cannot be set if the matcher is already started. In case of error, you can get the error text by calling <a href="#CDKGetLastError">CDKGetLastError</a>
*/
int32_t CDK_API CDKPlateFingerprintMatcherSetDictionary(CDKPlateFingerprintMatcher* pMatcher, const uint8_t* pBuffer, uint32_t uSize);

/*!
	Sets the <a href="#PCDKPLATEFINGERPRINTMATCHERSAVEDICTIONARYFUNCTION">save Dictionary callback</a> for this Matcher.<br/>
	It is highly recommended to set this callback.
	@param[in] pMatcher the matcher
	@param[in] saveFunction a pointer to the callback function
	@param[in] pUser callback user data
*/
void CDK_API CDKPlateFingerprintMatcherSetSaveDictionaryCallback(CDKPlateFingerprintMatcher* pMatcher, PCDKPLATEFINGERPRINTMATCHERSAVEDICTIONARYFUNCTION saveFunction, void* pUser);

/*!
	Starts a matcher
	@param[in] pMatcher the matcher
	@returns 1 on success.In case of error, you can get the error text by calling <a href="#CDKGetLastError">CDKGetLastError</a>
*/
int32_t CDK_API CDKPlateFingerprintMatcherStart(CDKPlateFingerprintMatcher* pMatcher);


	
/*!
Compares 2 fingerprints, and says if they are the same
@param[in] pMatcher the matcher
@param[in] pBuffer1 binary data containing the first fingerprint to compare
@param[in] uSize1 first fingerprint size
@param[in] pBuffer2 binary data containing the second fingerprint to compare
@param[in] uSize2 second fingerprint size
@returns The comparison result: 0 if the fingerprints are different, 1 if they are the same, or -1 in case of error. In case of error, you can get the error text by calling <a href="#CDKGetLastError">CDKGetLastError</a>
*/
int32_t CDK_API CDKPlateFingerprintMatch(CDKPlateFingerprintMatcher* pMatcher, const uint8_t* pBuffer1, uint32_t uSize1, const uint8_t* pBuffer2, uint32_t uSize2);

/*!
for testing only...
*/
int32_t CDK_API CDKPlateFingerprintMatchEx(CDKPlateFingerprintMatcher* pMatcher, const uint8_t* pBuffer1, uint32_t uSize1, const uint8_t* pBuffer2, uint32_t uSize2, float* pfResult);

#ifdef __cplusplus
}
#endif

#endif //CDKPLATEFINGERPRINTMATCHER_H