#!/bin/sh -f
#############


#setting paths...

# alienv enter O2/latest-dev-o2
#alienv enter O2Physics/latest
#source /home/ceres/marin/.bashrc
#to be used for new tracking
#alienv enter  O2/latest

#simulation with FT3
alienv enter  O2Physics/latest, O2/latest

echo ${PATH}
echo ${LD_LIBRARY_PATH}



#setting dirs...

main_DIR=/misc/alidata120/alice_u/marin/ALICE3/electron-pack
running_DIR=${main_DIR}/runningPbPb220623
result_DIR=${main_DIR}/resultsPbPb220623
condor_DIR=${main_DIR}/condor_logsPbPb220623

mkdir -p ${condor_DIR}
mkdir -p ${running_DIR}
mkdir -p ${result_DIR}


cd ${main_DIR}
#01
for m in  1000

#800 801 802 803 804 805 806 807 808 809 810 811 812 813 814 815 816 817 818 819 820 821 822 823 824 825 826 827 828 829 830 831 832 833 834 835 836 837 838 839 840 841 842 843 844 845 846 847 848 849 850 851 852 853 854 855 856 857 858 859 860 861 862 863 864 865 866 867 868 869 870 871 872 873 874 875 876 877 878 879 880 881 882 883 884 885 886 887 889 890 891 892 893 894 895 896 897 898 899  


#701 702 703 704 705 706 707 708 709 710 711 712 713 714 715 716 717 718 719 720 721 722 723 724 725 726 727 728 729 730 731 732 733 734 735 736 737 738 739 740 741 742 743 744 745 746 747 748 749 750 751 752 753 754 755 756 757 758 759 760 761 762 763 764 765 766 767 768 769 770 771 772 773 774 775 776 777 778 779 780 781 782 783 784 785 786 787 788 789 790 791 792 793 794 795 796 797 798 799  


#501 502 503 504 505 506 507 508 509 510 511 512 513 514 515 516 517 518 519 520 521 522 523 524 525 526 527 528 529 530 531 532 533 534 535 536 537 538 539 540 541 542 543 544 545 546 547 548 549 550 551 552 553 554 555 556 557 558 559 560 561 562 563 564 565 566 567 568 569 570 571 572 573 574 575 576 577 578 579 580 581 582 583 584 585 586 587 588 589 590 591 592 593 594 595 596 597 598 599 600 601 602 603 604 605 606 607 608 609 610 611 612 613 614 615 616 617 618 619 620 621 622 623 624 625 626 627 628 629 630 631 632 633 634 635  636 637 638 639 640 641 642 643 644 645 646 647 648 649 650 651 652 653 654 655 656 657 658 659 660 661 662 663 664 665 666 667 668 669 670 671 672 673 674 675 676 677 678 679 680 681 682 683 684 685 686 687 688 689 690 691 692 693 694 695 696 697 698 699 

#




    # 301 302 303 304 305 306 307 308 309 310 311 312 313 314 315 316 317 318 319 320 321 322 323 324 325 326 327 328 329 330 331 332 333 334 335 336 237 338 339 340 341 342 343 344 345 346 347 348 349 350 351 352 353 354 355 356 357 358 359 360 361 362 363 364 365 366 367 368 369 370 371 372 373 374 375 376 377 378 379 380 381 382 383 384 385 386 387 388 389 390 391 392 393 394 395 396 397 398 399


	    #   201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 256 257 258 259 260 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275 276 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292 293 294 295 296 297 298 299
 do
 
     cd ${running_DIR}
        wrk_dir=wrk_${m}
        mkdir ${wrk_dir}
        export result_dir=${result_DIR}/eve$m
        mkdir -p ${result_dir}
        cd ${wrk_dir}



        cp ${main_DIR}/run_simulation.sh  .
        cp ${main_DIR}/RecoDecay.h  .
        cp ${main_DIR}/trigger_multiplicity.C  .
        cp ${main_DIR}/runtracking.C   .
        cp ${main_DIR}/run_analysis_example.C  .

#        cp ${main_DIR}/run_strangenesstracking_01.C  .
#        cp ${main_DIR}/run_conversiontracking_01.C  .

        cp ${main_DIR}/jobscript_sim .
	#   source run_simulation.sh
        #root.exe -q -b run_strangenesstracking_01.C+

        condor_cmd=jobscript_sim${m}.cmd
        jobscript=jobscript_sim 
        LOG=${condor_DIR}/jobscript_sim${m}.LOG


           
#make a cmd file for submit...
           cat << EOF > $condor_cmd
 
universe        = vanilla
Getenv          = true
executable      = ${jobscript}

#Requirements = (TARGET.Machine != "alice-serv14")
Requirements = (TARGET.Machine == "alice-serv10" ||TARGET.Machine == "alice-serv11" || TARGET.Machine == "alice-serv12" || TARGET.Machine == "alice-serv13")
#requirements = (Machine == "alice-serv10" || Machine == "alice-serv11" || Machine == "alice-serv12" || Machine == "alice-serv13" || Machine == "alice-serv14")

output          = ${condor_DIR}/jobscript_sim${m}.out
error           = ${condor_DIR}/jobscript_sim${m}.err
log             = ${condor_DIR}/jobscript_sim${m}.log
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
transfer_input_files = run_simulation.sh, RecoDecay.h, trigger_multiplicity.C, run_analysis_example.C, runtracking.C
#Requirements    = (Machine != "alice-serv14.physi.uni-heidelberg.de")

#requirements    =!stringListMember(Utsname Nodename, “alice-serv14")

queue
EOF



           condor_submit $condor_cmd   

#  requirements    = (Machine != "alice-serv14.physi.uni-heidelberg.de")
	   sleep 1

           cd ../../
echo $m

done






