stopped=0
hist=()
ANS=0

while [[ $stopped -ne 1 ]]; do
    read -p ">> " expression
    read -r num1 oper num2  <<< "$expression"
    read ANS < ans.txt
    if [ "$num1" == "EXIT" ] ; then
        ((stopped+=1))
        break
    fi
    if [ "$num1" == "HIST" ]
	then
		printf '%s\n' "${hist[@]}"
		continue
	fi

    if [ "$num1" == "ANS" ] ; then
        num1=$ANS
    fi 
    
    if [ "$num2" == "ANS" ] ; then
        num2=$ANS
    fi

    if [ $num1 -eq $ANS ] ; then
		if [ ${#expression} -le 5 ] ; then 
        	echo $ANS 
        	continue
		fi
    fi
    
	if [ "$oper" == "*" ] ; then
		oper="x"
	elif [ "$oper" == "x" ] ; then
		oper="*"
	fi

    case $oper in 
        +) res=`echo "scale=2; $num1 + $num2" | bc`;;
        -) res=`echo "scale=2; $num1 - $num2" | bc`;;
        x) res=`echo "scale=2; $num1 * $num2" | bc`;;
        /)
            if [ $num2 -eq 0 ] ; then 
                echo "MATH ERROR"
				continue
            else
                res=`echo "scale=2; $num1 / $num2" | bc`
            fi
        ;;
        *) 
            echo "SYNTAX ERROR"
			continue
        ;;
    esac

	ANS=$res
	echo $res
    echo $res > ans.txt
	if [ ${#hist[@]} -ge 5 ] ; then
		hist=("${hist[@]:1}")
	fi 
		
	expression=$expression" = "$res
	hist+=("$expression") 
done
