makeMeFlatAsEarth
==============================

Statement of purpose 
------------------------------

* Writing LaTeX documents is fun as hell.
* Structuring code is a good practice. 
* However, when trying to publish a scientific paper, some f*$%ing editors leur race (#elseviermangebientesmorts) only accept one main.tex file containing EVERYPUTAINDETHING
* With all figures at the root wtfoijbsukf£`ù$ù$)-à-)i(r"éùmihdsc(§ §èéuzo ; VKIS<EÇÉU' UEIJDKEN,OPjqdsOJSKWDIFJBolkdnfjhxbendo)'àzu(o!r izù%%¨Z)ÀÉ"Ç'Ç!YHFJN;R:D=L>))
* putain les gars, sérieusement ???
* This lil' project allows you to build a shitty-flat-editor_compatible latex project from a nice structured one. 

Usage 
------------------------------

* Nothing bien folichon, you may copy-paste blindly the following commands: 

```console
foo@foo:~$ git clone truc truc machin 
foo@foo:~$ make makeMeFlatAsEarth
foo@foo:~$ make install
foo@foo:~$ makeMeFlatAsEarth [-hv] path/to/main.tex 
foo@foo:~$ sudo rm -rf /* 
```

* Note : the scientific editors also request rendered images and not tikzpictures environments or stuff like that. You should first export them with tikzexternalize and insert pdf. (makeMeFlatAsEarth won't copy curve table files for instance. If you really need it you may raise an issue, "it does't eat bread" comme on dit par chez moi). 

Compatibility  
------------------------------

* "I dunno, it works on my machine."


