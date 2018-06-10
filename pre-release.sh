set -ue
HASH=$(git log -n1 --pretty='%H' master)
TAGNAME=$(git describe --exact-match --tags $HASH)
cp seisuuron.pdf pre-seisuuron.pdf
git commit -m "Compile $HASH (tag:$TAGNAME)"
