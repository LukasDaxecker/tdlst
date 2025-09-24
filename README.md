# tdlst

## Description

Lightweigth temporary TODO-list

## Install

```
git clone git@github.com:LukasDaxecker/tdlst.git
cd tdlst
chmod +x install.sh
./install.sh
cd ..
rm -rf tdlst
```

## Help

tdlst \[-C | -D|-F <TITLE> | -A <TITLE DESC DEADLINE\] 

* none ... Prints current list
* -C   ... Prints list of completed tasks
* -D <TITLE> ... Delete task
* -F <TITLE> ... Finish task
* -A <PARAM> ... Add task
  * PARAM:
  * TITLE     ... Title of task
  * DESC      ... Task description
  * DEADLINE  ... Deadline   
