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

The CursorWindow implementation is NOW based on Android 4.4 and exports
its native functionality through static native functions.

WARNING: Not expected to support 64-bit build since this implementation uses 32-bit
integers for native pointer handles. This is solved in the Android 5.x/Android M
sources.

