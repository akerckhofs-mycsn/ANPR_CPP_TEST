/*! \file

CDKMsg : messages exchanged between the CDK and the Survision equipment

*/

#ifndef CDKMSG_H
#define CDKMSG_H

#ifdef __cplusplus
extern "C"	{
#endif

#ifndef CDK_API
#define  CDK_API
#endif

#ifndef CDK_H
typedef struct _cdk CDK;
#endif

/*! <summary>struct</summary>

    A message
*/
typedef struct  _CDKMsg CDKMsg;

/*! <summary>struct</summary>

    An element of a message
*/
typedef struct  _CDKMsgElement CDKMsgElement;

/*! <summary>callback</summary>

    Callback called when <a href="#CDKMsgExport">CDKMsgExport</a> is executed
	@param[in] pData Piece of data generated from the CDKMsg exported
	@param[in] len Length of pData
	@param[in] pUser User data
	@returns CDK_OK if export is succesful, or 0 in case of error : the export will then be stopped
*/
typedef int32_t (*PCDKMSGEXPORTCALLBACK) (const uint8_t* pData, uint32_t len, void* pUser);

/*! <summary>callback</summary>

    Callback called when <a href="#CDKMsgImport">CDKMsgImport</a> is executed
	@param[in] pData Piece of data to be read
	@param[in] len Max length of pData
	@param[in] pUser User data
	@returns the len of data read, or -1 in case of error : the import will then be stopped
*/
typedef int32_t (*PCDKMSGIMPORTCALLBACK) (uint8_t* pData, uint32_t len, void* pUser);




/*!
	Converts the string value to a boolean.
	@param[in] str string	
	@returns 1 if str='true' or str='1', otherwise 0
*/
int32_t CDK_API CDKMsgStrToBool( const char* str );


/*!
	Compares 2 strings, in a case insensitive way. May be used to find elements name or attributes names
	@param[in] str1 first string to compare
	@param[in] str2 second string to compare
	@returns 1 if the strings are the same, 0 if they are different or at least one is NULL
*/
int32_t CDK_API CDKMsgStringEqual(const char* str1, const char* str2);

/*!
	Creates a new instance of CDKMsg	
	@returns The created CDKMsg or NULL on failure
*/
CDKMsg CDK_API * CDKMsgCreate();

/*!
	Returns the read-only state of a CDKMsg. When a CDKMsg is read-only, it is possible to use <a href="#CDKMsgAddRef">CDKMsgAddRef</a>.
	@param[in] pMsg CDKMsg	
	@returns 1 if read only
*/
int32_t CDK_API CDKMsgIsReadOnly(CDKMsg* pMsg);

/*!
	Changes the read-only state of a CDKMsg. Note that it is not possible to remove read-only if there is more than one reference to the CDKMsg (i.e. CDKMsgAddRef has been called at least once).
	@param[in] pMsg CDKMsg	
	@param[in] bReadOnly the new read-only state	
	@returns 1 if the state has been successfully changed
*/
int32_t CDK_API CDKMsgSetReadOnly(CDKMsg* pMsg, int32_t bReadOnly);

/*!
	Sets user data to a CDKMsg. This function cannot be called if the CDKMsg is read only.
	@param[in] pMsg CDKMsg	
	@param[in] pData user data
	@returns 1 on success
*/
int32_t CDK_API CDKMsgSetUserData(CDKMsg* pMsg, void* pData);

/*!
	Returns user data of a CDKMsg.
	@param[in] pMsg CDKMsg	
	@returns user data
*/
void CDK_API * CDKMsgGetUserData(CDKMsg* pMsg);

/*! 
	Removes any element in a CDKMsg. This function cannot be called if the CDKMsg is read only.
	@param[in] pMsg CDKMsg to clear
*/
int32_t CDK_API CDKMsgClear( CDKMsg* pMsg );

/*! 
	Deletes a CDKMsg. All its subelements are automatically deleted.
	@param[in] pMsg Pointer to the message
*/
void CDK_API CDKMsgDestroy( CDKMsg* pMsg );

/*!
	Returns the root element of a CDKMsg
	@param[in] pMsg The message
	@returns The child, or NULL if there is no such element.
*/
CDKMsgElement CDK_API * CDKMsgChild(CDKMsg* pMsg);

/*!
	Exports a message. The data will be synchronously sent via the callback function <a href="#PCDKMSGEXPORTCALLBACK">PCDKMSGEXPORTCALLBACK</a><br/>
	The message must have been previously created with CDKMsgCreate. The message has to be destroyed by the application.
	@param[in] pMsg The message to export
	@param[in] exportCallback a pointer to the callback function
	@param[in] pUser callback user data
	@returns CDK_OK if export is succesful, i.e. if exportCallback never returned 0
*/
int32_t CDK_API CDKMsgExport(CDKMsg* pMsg, PCDKMSGEXPORTCALLBACK exportCallback, void* pUser); 

/*!
	Imports a message. The data is synchronously read via the callback function <a href="#PCDKMSGIMPORTCALLBACK">PCDKMSGIMPORTCALLBACK</a>. <br/>
	The message must have been previously created with CDKMsgCreate. The message has to be destroyed by the application.
	@param[in] pMsg The message to import
	@param[in] importCallback a pointer to the callback function
	@param[in] pUser callback user data
	@returns CDK_OK if import is succesful, i.e. if importCallback never returned -1
*/
int32_t CDK_API CDKMsgImport(CDKMsg* pMsg, PCDKMSGIMPORTCALLBACK importCallback, void* pUser); 

/*!
	Exports a message in a binary buffer. <br/>
	The buffer must have been allocated by the application.<br/>
	The message must have been previously created with CDKMsgCreate. The message has to be destroyed by the application.
	@param[in] pMsg The message to export
	@param[in] pBuffer The output buffer
	@param[in] uBufferSize the size of the buffer.
	@returns the size of the written data in the buffer, or CDK_FAIL(0) if the given buffer is too small.
*/
int32_t CDK_API CDKMsgExportToBinaryArray(CDKMsg* pMsg, uint8_t* pBuffer, uint32_t uBufferSize);

/*!
	Imports a message from a binary buffer. <br/>
	The message must have been previously created with CDKMsgCreate. The message has to be destroyed by the application.
	@param[in] pMsg The message to import
	@param[in] pBuffer The input buffer
	@param[in] uBufferSize the size of the buffer
	@returns CDK_OK if import is succesful.
*/
int32_t CDK_API CDKMsgImportFromBinaryArray(CDKMsg* pMsg, const uint8_t* pBuffer, uint32_t uBufferSize);

/*! 
	Returns the CDK instance that created the message. This field is filled only for messages received asynchronously from an equipment.
	@param[in] pMsg Pointer to the message
	@returns the CDK instance.
*/
CDK CDK_API * CDKMsgGetCDK(CDKMsg* pMsg);

/*!
	Creates a copy of a CDKMsg. 
	@param[in] pMsg the message to copy
	@returns the new message
*/
CDKMsg CDK_API * CDKMsgCopy(CDKMsg* pMsg);

/*!
	Adds a reference to a read-only CDKMsg. The reference count is decreased when calling <a href="#CDKMsgDestroy">CDKMsgDestroy</a>.<br/>
	The message is detroyed when there is no more references to it.<br/>
	This function is thread safe.
	@param[in] pMsg the message
	@returns CDK_OK on success, CDK_FAIL if the CDKMsg is NOT read only.
*/
int32_t CDK_API CDKMsgAddRef(CDKMsg* pMsg);

/*!
	Sets the root element of the message. <br/>
	The element must have been previously created (with <a href="#CDKMsgElementCreate">CDKMsgElementCreate</a>). <br/>
	If the message already contains a root element, this old root element is destroyed.<br/>
	This function cannot be called if pChildElement is already owned by another element or message, or if the message is read only.	
	@param[in] pMsg the message
	@param[in] pChildElement the element to add to the message.
	@returns CDK_OK on success, CDK_FAIL otherwise
*/
int32_t CDK_API CDKMsgSetChild(CDKMsg* pMsg, CDKMsgElement* pChildElement) ;

/*!
	Creates a CDKMsgElement with the specified name
	@param[in] strName Name of the CDKMsgElement, in ASCII
	@returns The created CDKMsgElement or NULL if an error occured
*/
CDKMsgElement CDK_API * CDKMsgElementCreate( const char* strName );

/*!
	Changes the name of a CDKMsgElement
	@param[in] pElement the element to rename
	@param[in] strName new name, in ASCII
	@returns CDK_OK on success
*/
int32_t CDK_API CDKMsgElementSetName(CDKMsgElement* pElement, const char* strName ); 

/*!
	Destroys an element. <br/>
	If the element is owned by a read only message, it cannot be destroyed.<br/>
	If the element is a sub element of another element, it is removed from the children list of its parent element.
	@param[in] pElement the element to destroy
	@returns CDK_OK on success, CDK_FAIL if the message is read only.
*/
int32_t CDK_API CDKMsgElementDestroy(CDKMsgElement* pElement);

/*!
	Detachs an element from its parent. The element is removed from the children list of its parent element, but is not destroyed : it is owned by the application.<br/>
	If the element is owned by a read only message, it cannot be detached.<br/>
	@param[in] pElement the element to detach
	@returns CDK_OK on success, CDK_FAIL if the message is read only or the element has already no parent.
*/
int32_t CDK_API CDKMsgElementDetach(CDKMsgElement* pElement);

/*!
	Returns a CDKMsgElement name
	@param[in] pElement The element
	@returns the name of the element
*/
const char CDK_API * CDKMsgElementName(CDKMsgElement* pElement);

/*!
	Returns the parent of a CDKMsgElement
	@param[in] pElement The element
	@returns the parent element , or NULL if the element has no parent element
*/
CDKMsgElement CDK_API * CDKMsgElementParent(CDKMsgElement* pElement);

/*!
	Returns the message containing a CDKMsgElement
	@param[in] pElement The element
	@returns the message , or NULL if the element is not in a message
*/
CDKMsg CDK_API * CDKMsgElementMsg(CDKMsgElement* pElement);

/*!
	Sets an attribute of a CDKMsgElement. This function cannot be called if the CDKMsg is read only.
	@param[in] pElement CDKMsgElement to edit
	@param[in] strKey Name of the attribute, in ASCII 
	@param[in] strValue Value to set to the attribute, in UTF-8 
*/
int32_t CDK_API CDKMsgElementSetAttribute( CDKMsgElement* pElement, const char* strKey, const char* strValue);

/*!
	Sets a signed integer attribute of a CDKMsgElement. This function cannot be called if the CDKMsg is read only.
	@param[in] pElement CDKMsgElement to edit
	@param[in] strKey Name of the attribute, in ASCII 
	@param[in] iValue Value to set to the attribute
*/
int32_t CDK_API CDKMsgElementSetAttributeInt( CDKMsgElement* pElement, const char* strKey, int32_t iValue);

/*!
	Sets a unsigned integer attribute of a CDKMsgElement. This function cannot be called if the CDKMsg is read only.
	@param[in] pElement CDKMsgElement to edit
	@param[in] strKey Name of the attribute, in ASCII 
	@param[in] uValue Value to set to the attribute
*/
int32_t CDK_API CDKMsgElementSetAttributeUInt( CDKMsgElement* pElement, const char* strKey, uint32_t uValue);

/*!
	Sets a 64bits integer attribute of a CDKMsgElement. This function cannot be called if the CDKMsg is read only.
	@param[in] pElement CDKMsgElement to edit
	@param[in] strKey Name of the attribute, in ASCII 
	@param[in] uValue Value to set to the attribute
*/
int32_t CDK_API CDKMsgElementSetAttributeInt64( CDKMsgElement* pElement, const char* strKey, int64_t iValue);

/*!
	Sets a boolean attribute of a CDKMsgElement. This function cannot be called if the CDKMsg is read only.
	@param[in] pElement CDKMsgElement to edit
	@param[in] strKey Name of the attribute, in ASCII 
	@param[in] bValue Value to set to the attribute
*/
int32_t CDK_API CDKMsgElementSetAttributeBool( CDKMsgElement* pElement, const char* strKey, int32_t bValue);

/*!
	Sets a float attribute of a CDKMsgElement. This function cannot be called if the CDKMsg is read only.
	@param[in] pElement CDKMsgElement to edit
	@param[in] strKey Name of the attribute, in ASCII 
	@param[in] fValue Value to set to the attribute
*/
int32_t CDK_API CDKMsgElementSetAttributeFloat( CDKMsgElement* pElement, const char* strKey, float fValue);

/*!
	Removes an attribute of a CDKMsgElement. This function cannot be called if the CDKMsg is read only.
	@param[in] pElement CDKMsgElement to edit
	@param[in] strKey Name of the attribute, in ASCII 
*/
int32_t CDK_API CDKMsgElementRemoveAttribute( CDKMsgElement* pElement, const char* strKey);

/*!
	Return the number of attributes of a CDKMsgElement. <br/>
	Each attribute name will be acccessible by its index with <a href="#CDKMsgElementAttributeName">CDKMsgElementAttributeName</a>.<br/>
	Each attribute value will be acccessible by its attribute name with <a href="#CDKMsgElementAttributeValue">CDKMsgElementAttributeValue</a>.<br/>
	@param[in] pElement The element
	@returns number of attributes in the element
*/
uint32_t CDK_API CDKMsgElementAttributeCount(CDKMsgElement* pElement);
/*!
	Returns an attribute's name
	@param[in] pElement The element
	@param[in] uIndex The index of the attribute
	@returns the name of the attribute, or NULL if the index is invalid
*/
const char CDK_API * CDKMsgElementAttributeName( CDKMsgElement* pElement, uint32_t uIndex );

/*!
	Returns an attribute's value
	@param[in] pElement The element
	@param[in] strKey The attribute's name
	@returns The attribute value in UTF-8, or NULL if the attribute does not exist.
*/
const char CDK_API * CDKMsgElementAttributeValue( CDKMsgElement* pElement, const char* strKey );

/*!
	Adds a child element to the element. <br/>
	The child element must have been previously created (with <a href="#CDKMsgElementCreate">CDKMsgElementCreate</a>). <br/>
	This function cannot be called if the child element is already owned by another element, or if the element is owned by a read only message.	
	@param[in] pElement The element
	@param[in] pChildElement The element to add
	@returns CDK_OK if success. To check error use <a href="#CDKGetLastError">CDKGetLastError</a>
*/
int32_t CDK_API CDKMsgElementAddChild( CDKMsgElement* pElement, CDKMsgElement* pChildElement );

/*!
	Creates a copy of a CDKMsgElement. 
	@param[in] pElt the message to copy
	@returns the new element
*/
CDKMsgElement CDK_API * CDKMsgElementCopy(CDKMsgElement* pElt);


/*!
	Return the number of children elements in a CDKMsgElement, having a specific name.
	@param[in] pElement The element
	@param[in] strName Name of the children, or NULL for all children
	@returns the children count
*/
uint32_t CDK_API CDKMsgElementChildCount( CDKMsgElement* pElement, const char* strName );


/*!
	Returns the first child of a CDKMsgElement, having a specific name.
	@param[in] pElement The parent element
	@param[in] strName of the children, or NULL for all children
	@returns The first child of the message with this name, or NULL if there is no such element.
*/
CDKMsgElement CDK_API * CDKMsgElementFirstChild( CDKMsgElement* pElement, const char* strName );

/*!
	Returns the next child of a CDKMsgElement.
	@param[in] pElement The parent element
	@param[in] pChildElement The current child element
	@param[in] strName of the children, or NULL for all children
	@returns The child after pChildElement, or NULL if there is no such element.
*/
CDKMsgElement CDK_API * CDKMsgElementNextChild( CDKMsgElement* pElement, CDKMsgElement* pChildElement, const char* strName);


/*!
	Sets binary content in a CDKMsgElement. This function cannot be called if the CDKMsg is read only. Note that the content is deeply copied.
	@param[in] pElement The element
	@param[in] strContent Binary content, does not have to be NULL terminated
	@param[in] uContentSize Length of binary content
	@returns CDK_OK on success. To check error use <a href="#CDKGetLastError">CDKGetLastError</a>
*/
int32_t CDK_API CDKMsgElementSetContentBinary( CDKMsgElement* pElement, const uint8_t* strContent, uint32_t uContentSize);

/*!
	Returns the element's content size
	@param[in] pElement The element
	@returns the content size.
*/
uint32_t CDK_API CDKMsgElementContentSize(CDKMsgElement* pElement);

/*!
	Returns a pointer to the element's content. Note that in the C version, the data is not copied, and in the .Net version, the data is deeply copied.
	@param[in] pElement The element
	@returns the content data, or NULL if there is no data.
*/
const uint8_t CDK_API * CDKMsgElementContent(CDKMsgElement* pElement);

/*!
	Merge element pElt in pEltDest. pEltDest will then contain attributes and sub elements from the 2 elements.
	@param[in] pEltDest the destination element
	@param[in] pElt the second element
	@param[in] ppEltDiff a pointer to a diffence element. If set, the function will create an element and fill it with differences between pEltDest and pElt. Note that this element is created even if there are no difference between compared elements.
	@param[in] bAddNewStuff if 1, Any attribute or sub element that exists in pElt will be added in pEltDest, otherwise only attributes and sub elements that already exist in pEltDest will be modified
	@returns 1 if pEltDest has been changed, otherwise 0
*/
int32_t CDK_API CDKMsgElementMerge( CDKMsgElement* pEltDest, CDKMsgElement* pElt, CDKMsgElement** ppEltDiff, int32_t bAddNewStuff );

#ifdef __cplusplus
}
#endif

#endif //CDKMSG_H
