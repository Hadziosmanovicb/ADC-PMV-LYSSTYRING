# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/benjamin/Desktop/skole/2 semester/data teknik/Opgave 5/build/_deps/unity-src"
  "/Users/benjamin/Desktop/skole/2 semester/data teknik/Opgave 5/build/_deps/unity-build"
  "/Users/benjamin/Desktop/skole/2 semester/data teknik/Opgave 5/build/_deps/unity-subbuild/unity-populate-prefix"
  "/Users/benjamin/Desktop/skole/2 semester/data teknik/Opgave 5/build/_deps/unity-subbuild/unity-populate-prefix/tmp"
  "/Users/benjamin/Desktop/skole/2 semester/data teknik/Opgave 5/build/_deps/unity-subbuild/unity-populate-prefix/src/unity-populate-stamp"
  "/Users/benjamin/Desktop/skole/2 semester/data teknik/Opgave 5/build/_deps/unity-subbuild/unity-populate-prefix/src"
  "/Users/benjamin/Desktop/skole/2 semester/data teknik/Opgave 5/build/_deps/unity-subbuild/unity-populate-prefix/src/unity-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/benjamin/Desktop/skole/2 semester/data teknik/Opgave 5/build/_deps/unity-subbuild/unity-populate-prefix/src/unity-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/benjamin/Desktop/skole/2 semester/data teknik/Opgave 5/build/_deps/unity-subbuild/unity-populate-prefix/src/unity-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
