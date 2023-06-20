#include "highscore.h"

highscore::highscore(QWidget *parent): QTextBrowser(parent)
{

}

bool highscore::writeFile(QString filename, QString text){
    QFile file(filename);

    if(file.open(QIODevice::Append|QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << text <<"\n";
    }

    file.close();
    return true;
}

QStringList highscore::readFile(QString filename){

    QFile file(filename);
    QStringList null;
    if(!file.exists()){
        qCritical() << "File not found!";
        return null;
    }

    if(!file.open(QIODevice::ReadOnly)){
        qCritical() << "Could not open file!";
        qCritical() << file.errorString();
        return null;
    }
    //read all text data from file
    QTextStream stream(&file);
    QString alldat;
    while (!stream.atEnd()){
        QString line = stream.readLine();
        alldat = alldat + line + ".";
    }

    file.close();
    QList<QString> names;
    //Seperate text into list
    QStringList sep = alldat.split(".");
   // qInfo()<< sep.length();
    for (int i = 0; i <= sep.length() - 2 ; ++i ) {
        //seperate list into sublist
        QStringList sepname = sep[i].split(",");
//        qInfo()<< "sepname "<<sepname;
//        qInfo()<< sepname.length();
        for (int j = 0; j < sepname.length() ; ++j ) {
            QStringList sepnum = sepname[j].split(" ");
            QString name = sepnum[0];
            bool in_list = false;
            int win = 0, loss = 0;

            if ((sepnum[1]) == "0")
                loss++;
            if ((sepnum[1]) == "1")
                win++;

            for (int k = 0; k < names.length(); ++k ) {
                QString tempName = names[k];
                tempName.remove(name.length(),4);
                if(name==tempName){
                    in_list = true;
                    //replace win and loss
                    QString line,wins,losses;
                    line = names[k];
                    wins = line;
                    wins.remove(line.length()-2,2);
                    wins.remove(0, wins.length()-1);

                    losses = line;
                    losses.remove(0,line.length()-1);

                    win = win + wins.toInt();
                    loss = loss + losses.toInt();

                    names[k] = name+QString(" %1 %2").arg(win).arg(loss);

                }
            }
            if(!in_list)
                names.append(name+QString(" %1 %2").arg(win).arg(loss));
        }
    }
    return names;
}

QStringList highscore::findMostWins(QStringList list){
    QStringList arr = list;
    int n = list.size();
    bool swapped;
    //make a only wins list with wins in the same order as original list
    for (int i = 0; i < arr.length() ; ++i) {
        QString line,wins;
        line = arr[i];
        wins = line;
        wins.remove(line.length()-2,2);
        wins.remove(0, wins.length()-1);
        arr[i]=wins;
    }
    //bubblesort
    for (int i = 0; i < n - 1; ++i)
    {
        swapped = false;

        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] < arr[j + 1])
            {
                // Swap arr[j] and arr[j + 1]
                QString temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;

                QString temp2 = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp2;

                swapped = true;
            }
        }

        // If no two elements were swapped in the inner loop,
        // then the array is already sorted
        if (!swapped)
            break;
    }
    //qInfo()<<arr;
    return list;
}


QString highscore::buatify(QStringList list){
    QString out = "Name\tWins\tLoss\n"
                  "_______________________________\n";
    for (int i = 0; i< list.length() ; ++i) {
        QString tempName,line,wins,losses;
        line = list[i];

        tempName = line;
        tempName.remove(line.length()-4,4);

        wins = line;
        wins.remove(line.length()-2,2);
        wins.remove(0, wins.length()-1);

        losses = line;
        losses.remove(0,line.length()-1);

        out = out + QString("%1\t%2\t%3\n\n").arg(tempName).arg(wins).arg(losses);
    }
    return out;
}
