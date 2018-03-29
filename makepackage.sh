cp build/x64/pl Packagex64/bin/pl
cd PackageOutput/x64/
rm *.deb
dpkg-deb -b ../../Packagex64/ plx64.deb

cd ../../

cp build/x86/pl Packagex86/bin/pl
cd PackageOutput/x86/
rm *.deb
dpkg-deb -b ../../Packagex86/ plx86.deb
