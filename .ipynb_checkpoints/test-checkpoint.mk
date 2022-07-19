all:  log/sample1.done  log/sample2.done 
	echo "All"

log/sample1.done: log/sample1.Job_1.done log/sample1.Job_2.done log/sample1.Job_3.done
	touch log/sample1.done

log/sample1.Job_1.done:
	echo "Sample1 test1" && touch log/sample1.Job_1.done

log/sample1.Job_2.done: log/sample1.Job_1.done
	echo "Sample1 test2" && touch log/sample1.Job_2.done

log/sample1.Job_3.done: log/sample1.Job_1.done log/sample1.Job_2.done
	echo "Sample1 test3" && touch log/sample1.Job_3.done


log/sample2.done: log/sample2.Job_1.done log/sample2.Job_2.done log/sample2.Job_3.done
	touch log/sample2.done

log/sample2.Job_1.done:
	echo "Sample2 test1" && touch log/sample2.Job_1.done

log/sample2.Job_2.done: log/sample2.Job_1.done
	echo "Sample2 test2" && touch log/sample2.Job_2.done

log/sample2.Job_3.done: log/sample2.Job_1.done log/sample2.Job_2.done
	echo "Sample2 test3" && touch log/sample2.Job_3.done


