# CMake generated Testfile for 
# Source directory: C:/Users/davyd/Desktop/lab_BigInt/Tests
# Build directory: C:/Users/davyd/Desktop/lab_BigInt/build/Tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(Tests "C:/Users/davyd/Desktop/lab_BigInt/build/Tests/Debug/Tests.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(Tests "C:/Users/davyd/Desktop/lab_BigInt/build/Tests/Release/Tests.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(Tests "C:/Users/davyd/Desktop/lab_BigInt/build/Tests/MinSizeRel/Tests.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(Tests "C:/Users/davyd/Desktop/lab_BigInt/build/Tests/RelWithDebInfo/Tests.exe")
else()
  add_test(Tests NOT_AVAILABLE)
endif()
