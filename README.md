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

tdlst \[-C | -d|-f <ID> | -D|-F <TITLE> | -A <TITLE DESC DEADLINE\] 

* none ... Prints current list
* -C   ... Prints list of completed tasks
* -d <ID> ... Delete task given ID
* -f <ID> ... Finish task given ID
* -D <TITLE> ... Delete task given title
* -F <TITLE> ... Finish task with given title
* -A <PARAM> ... Add task
  * PARAM:
  * TITLE     ... Title of task
  * DESC      ... Task description
  * DEADLINE  ... Deadline   
