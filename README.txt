Android sqlcipher cursor query native driver (test)
===================================================

Native implementation of sqlcipher functionaity based on
sqlcipher/android-database-sqlcipher in the following classes:
- com.test.db.CursorWindow
- io.liteglue.SQLiteNative

These classes can be used to build a version of the Android sqlite database
classes that can be used to access SQLCipher or other sqlite derivatives
such as Spatialite.

SQLiteNative, based on Android-sqlite-native-driver and generated using Gluegen,
exports basic sqlite access functionaity through some static native functions.

The CursorWindow implementation is NOW based on Android 5.0/5.1 and exports
its native functionality through static native functions.

This implementation now uses 64-bit pointer handles and *should* 64-bit CPU safe.

