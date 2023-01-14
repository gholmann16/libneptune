#include <appimage/update.h>
#include <iostream>
#include <string>
#include <cstring>
#include <thread>

using namespace std;
namespace appimage::update

{
class Updater;
}

extern "C" int update_appimage(char * appname) {
    appimage::update::Updater updater(appname, true);

    bool updateAvailable;
    updater.checkForChanges(updateAvailable);

    if (!updateAvailable) {
        // log status messages before exiting
        printf("No updates found.\n");

        // return error state
        return 1;
    }

    if (updateAvailable) {
        printf("Update availble! Updating %s.\n", appname);
        updater.start();

        // isDone() returns true as soon as the update has finished
        // error handling is performed later
        while (!updater.isDone()) {
            // sleep for e.g., 100ms, to prevent 100% CPU usage
            this_thread::sleep_for(chrono::milliseconds(100));

            double progress;
            // as with all methods, check for error
            if (!updater.progress(progress)) {
                printf("Call to progress() failed\n");
                // return error state
                return 1;
            }

            // fetch all status messages
            // this is basically the same as before
            string nextMessage;
            while (updater.nextStatusMessage(nextMessage)) 
                ;
            if (updater.hasError()) {
                printf("Error occurred. See previous messages for details.\n");
                // return error state
                return 1;
            }
        }
        char temp[300];
        strcpy(temp, appname);
        strcat(temp, ".zs-old");
        remove(temp);
    }

    printf("%s successfully updated!\n", appname);
    return 0;
}

extern "C" int check_updateability(char * appname) {
    appimage::update::Updater updater(appname, true);
    string test;
    updater.describeAppImage(test);
    if (test.find("Assembled ZSync URL") != std::string::npos)
        return 1;
    return 0;
}