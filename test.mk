all:  log/Job_1.done log/Job_2.done log/Job_3.done

log/Job_1.done:
	echo "test1" && touch log/Job_1.done

log/Job_2.done: log/Job_1.done
	echo "test2" && touch log/Job_2.done

log/Job_3.done: log/Job_1.done log/Job_2.done
	echo "test3" && touch log/Job_3.done


