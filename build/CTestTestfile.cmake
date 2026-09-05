# CMake generated Testfile for 
# Source directory: /home/syswraith/code/scoundrel
# Build directory: /home/syswraith/code/scoundrel/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test("ValgrindMemCheck" "/usr/bin/valgrind" "--leak-check=full" "--show-leak-kinds=all" "--track-origins=yes" "--errors-for-leak-kinds=all" "--error-exitcode=1" "/home/syswraith/code/scoundrel/build/main")
set_tests_properties("ValgrindMemCheck" PROPERTIES  _BACKTRACE_TRIPLES "/home/syswraith/code/scoundrel/CMakeLists.txt;35;add_test;/home/syswraith/code/scoundrel/CMakeLists.txt;0;")
