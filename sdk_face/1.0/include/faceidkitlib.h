#ifndef FACEIDKIT_LIBRARY_H
#define FACEIDKIT_LIBRARY_H
#define FACEIDKIT_EXPORTS
#if defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__WIN64__)
#if defined(FACEIDKIT_EXPORTS)
#define LIBRARY_PREFIX extern "C" __declspec(dllexport)
#else
#define LIBRARY_PREFIX extern "C" __declspec(dllimport)
#endif /* FACEIDKIT_EXPORTS */
#elif defined(linux) || defined(__linux)
#define EXPORT_PREFIX
#endif
/**
*  \brief FaceIDKIT Biometric Library
*/

//start and stop functions
/**
*  \brief Initialize the library
*  \param [in] json_parameters_for_biometry All the parameters needed by the biometry, including license data
*  \return 0 if initialization is ok, other value with error code if initialization fails.
*  \details Function needed to be called before any other
*  Some parameters are minEyeDistance (default 25), maxEyeDistance (default 200), licenseFile(complete path to license file)
*/
LIBRARY_PREFIX int faceid_init_library(const char *json_parameters_for_biometry);
/**
*  \brief Terminates the library
*  \return 0 no problem with termination, other value error code
*
*  \details Needed function to be called to release resources
*/
LIBRARY_PREFIX int faceid_end_library();
/**
* \brief Get a face template from a face image
* \return 0 no problem at get the face template, other value error code
* \param [in] face_image Array with an image
* \param [in] face_image_size Array length for the image
* \param [out] face_template Output array with face template in a preallocated buffer
* \param [out] face_template_size Output array size with face template
*/
LIBRARY_PREFIX int faceid_get_template_from_image(const unsigned char *face_image, int face_image_size, unsigned char *face_template, int *face_template_size);

/**
* \brief Match two templates
* \return 0 no problem with termination, other value error code
* \param [in] face_template_target face template to match
* \param [in] face_template_source  face template to match
* \param [out] score match score
*/
LIBRARY_PREFIX int faceid_match_templates(const unsigned char *face_template_target, int face_template_target_size, const unsigned char *face_template_source, int face_template_source_size, float *score);

/**
* \brief Connect to database containing face templates data.
* \param [in] databaseString Database string connection like "database.db" for Sqlite, type=memory for Memory
* \return 0, connected;
*/
LIBRARY_PREFIX int connectToDatabase(const char *databaseString);

/**
* \brief Clear the face templates database
* \return 0, no problem with connection
*/
LIBRARY_PREFIX int clearDatabase();

/**
* \brief get the number of users in current opened face templates database
* \param [out] the number of users
* \return 0, no problem with operation
*/
LIBRARY_PREFIX int getNumberOfUsers(int* numberOfUsers);
/**
* \brief Add a face template creating a new  user in current template database
* \param [in] faceTemplate, a file with a face template for an user
* \param [out] userID, a new userid for the recently added user
* \return 0, no problem at add user
*/
LIBRARY_PREFIX int addUserToDatabase(const unsigned char *faceTemplate, int faceTemplateSize, int *userID);
/**
* \brief Add a face template to existent user in database
* \param [in] faceTemplate, a file with a face for an user
* \param [in] userID, an existent userid
* \return 0, no problem at add user
*/
LIBRARY_PREFIX int addTemplateToUserInDatabase(const unsigned char *faceTemplate, int faceTemplateSize, int userID);
/**
* \brief Add a user to current template database from file
* \param [in] faceImageFile, a file with a face for an user
* \param [out] userID, a new userid for the recently added user
* \return 0, no problem at add user
*/
LIBRARY_PREFIX int addUserToDatabaseFromFile(const char *faceImageFile, int *userID);
/**
* \brief Update an user in the current database adding the userfile face to their record
* \param [in] faceImageFile, a file with a face for an user
* \param [in] userID, the userid of user to update
* \return 0, no problem a add new record to user
*/
LIBRARY_PREFIX int addTemplateToUserInDatabaseFromFile(const char *faceImageFile, int userID);
/**
* \brief Remove an user from database
* \param [in] userID, the userid to remove
* \return 0, no problem a add new record to user
*/
LIBRARY_PREFIX int removeUser(int userID);
/**
* \brief Verify two user templates
* \param [in] user1Template, a face template
* \param [in] user2Template,a face template
* \param [out] score, the match score
* \return 0, no problem with connection
*/
LIBRARY_PREFIX int verify(const unsigned char *user1Template, int user1TemplateSize, const unsigned char *user2Template, int user2TemplateSize, int *score);
/**
* \brief identify user in current opened database
* \param [in] user1Template, a face template
* \param [out] userID, userid of found record
* \param [out] score, the match score of found record
* \return 0, no problem with connection
*/
LIBRARY_PREFIX int identify(const unsigned char *user1Template, int user1TemplateSize, int *userID, int *score);

#endif