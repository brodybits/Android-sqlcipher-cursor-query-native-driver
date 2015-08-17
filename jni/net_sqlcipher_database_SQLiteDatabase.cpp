/*
 * Copyright (C) 2006-2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#undef LOG_TAG
#define LOG_TAG "Database"

#include <cutils/log.h>

#include <jni.h>
#include <JNIHelp.h>

#include "sqlite3_exception.h"
#include "sqlcipher_loading.h"



namespace sqlcipher {


extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved) 
{ 
	JNIEnv *env;

	LOGI("JNI_OnLoad called");
	if (vm->GetEnv((void**) &env, JNI_VERSION_1_2) != JNI_OK) {
	    LOGE("Failed to get the environment using GetEnv()");
	    return -1;
	}
	
	LOGI("JNI_OnLoad register methods ");

	register_android_database_CursorWindow(env);

	// FUTURE TBD (??):
	//register_android_database_SQLiteDebug(env);

	return JNI_VERSION_1_2;

} 

/* throw a SQLiteException with the given message */
void throw_sqlite3_exception(JNIEnv* env, const char* message) {
    throw_sqlite3_exception(env, NULL, message);
}

/* throw a SQLiteException with a message appropriate for the error in handle
   concatenated with the given message
 */
void throw_sqlite3_exception(JNIEnv* env, sqlite3* handle, const char* message) {
    if (handle) {
        throw_sqlite3_exception(env, sqlite3_errcode(handle),
                                sqlite3_errmsg(handle), message);
    } else {
        // we use SQLITE_OK so that a generic SQLiteException is thrown;
        // any code not specified in the switch statement below would do.
        throw_sqlite3_exception(env, SQLITE_OK, "unknown error", message);
    }
}

/* throw a SQLiteException for a given error code, sqlite3message, and
   user message
 */
void throw_sqlite3_exception(JNIEnv* env, int errcode,
                             const char* sqlite3Message, const char* message) {
    const char* exceptionClass;
    switch (errcode) {
        // XXX TBD MARK correct android.database.sqlite exception:
        case SQLITE_IOERR:
            exceptionClass = "net/sqlcipher/database/SQLiteDiskIOException";
            break;
        case SQLITE_CORRUPT:
            exceptionClass = "net/sqlcipher/database/SQLiteDatabaseCorruptException";
            break;
        case SQLITE_CONSTRAINT:
           exceptionClass = "net/sqlcipher/database/SQLiteConstraintException";
           break;
        case SQLITE_ABORT:
           exceptionClass = "net/sqlcipher/database/SQLiteAbortException";
           break;
        case SQLITE_DONE:
           exceptionClass = "net/sqlcipher/database/SQLiteDoneException";
           break;
        case SQLITE_FULL:
           exceptionClass = "net/sqlcipher/database/SQLiteFullException";
           break;
        case SQLITE_MISUSE:
           exceptionClass = "net/sqlcipher/database/SQLiteMisuseException";
           break;
        default:
           exceptionClass = "net/sqlcipher/database/SQLiteException";
           break;
    }

    if (sqlite3Message != NULL && message != NULL) {
        char* fullMessage = (char *)malloc(strlen(sqlite3Message) + strlen(message) + 3);
        if (fullMessage != NULL) {
            strcpy(fullMessage, sqlite3Message);
            strcat(fullMessage, ": ");
            strcat(fullMessage, message);
            jniThrowException(env, exceptionClass, fullMessage);
            free(fullMessage);
        } else {
            jniThrowException(env, exceptionClass, sqlite3Message);
        }
    } else if (sqlite3Message != NULL) {
        jniThrowException(env, exceptionClass, sqlite3Message);
    } else {
        jniThrowException(env, exceptionClass, message);
    }
}


} // namespace sqlcipher
