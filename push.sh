if [ $# == 1 ]
then
  git add .
  git commit -m " $1 "
  git push origin master
else
  echo Usage: ./push.sh [comment]
fi
