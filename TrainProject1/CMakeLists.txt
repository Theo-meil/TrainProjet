# CMakeList.txt : projet CMake pour TrainProject1, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.
add_executable (TrainProject1 "Main.cpp" "Station.h" "Train.cpp" "Station.cpp" "Control.cpp" "Control.h" "Communication.cpp" "Communication.h" "Utilitaire.cpp" "Train.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TrainProject1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
