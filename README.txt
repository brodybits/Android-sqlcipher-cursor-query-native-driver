Android sqlcipher cursor query native driver (test)
===================================================

Native implementation of sqlcipher functionaity in the following classes:
- com.test.db.CursorWindow
- io.liteglue.SQLiteNative

These classes can be used to build a version of the Android sqlite database
classes that can be used to access SQLCipher or other sqlite derivatives
such as Spatialite.

SQLiteNative, based on Android-sqlite-native-driver and generated using Gluegen,
exports basic sqlite access functionaity through some static native functions.
It is desired for CursorWindow to export its native functionality through
static native functions, as it is done in newer versions of the Android project.

