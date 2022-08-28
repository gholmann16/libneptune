#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>

//External Libraries
#include <appimage/appimage.h>
#include <ezxml.h>

#define MAX_DIR_LEN 512
#define MAX_FILE_LENGTH 256 //might wanna look at these values in the future
#define VERBOSE 0

#include "lib/localupdate.h"

#include "functions/scrape.h"
#include "functions/betterexec.h"
#include "functions/extra.h"
#include "functions/checkfile.h"
#include "functions/checkroot.h"
#include "functions/registeration.h"
#include "functions/internal.h"

#include "commands/integrate.h"
#include "commands/remove.h"
#include "commands/uninstall.h"
#include "commands/install.h"
#include "commands/list.h"
#include "commands/reinstall.h"
#include "commands/find.h"
#include "commands/update.h"
#include "commands/run.h"
#include "commands/refresh.h"