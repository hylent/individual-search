#!/bin/bash
source ~/.bashrc
job_name="tiku_similar_buildindex"
JOB_INPUT="/user/caolin/buildindex/data/"
JOB_OUTPUT="/user/caolin/buildindex/post_07"

#datapath=$1
#dataname=`basename $1`
#datahadooppath="${JOB_INPUT}/${dataname}"
#echo "job:${job_name} START"
#
##创建hadoop文件夹
#pathexist=`hadoop fs -test -e ${JOB_INPUT}`
#if [ $pathexist -ne 0 ]
#then
#    ${HADOOP_HOME}/bin/hadoop fs -mkdir ${JOB_INPUT}
#else
#    echo "${JOB_INPUT} exist"
#fi

#拷贝文件
#${HADOOP_HOME}/bin/hadoop fs -copyFromLocal ${datapath} ${JOB_INPUT}
#fileexist=`hadoop fs -test -e ${datahadooppath}`
#if [ $pathexist -eq 0 ]
#then
#    echo "copy ${datapath} to ${datahadooppath} suc"
#else
#    echo "copy ${datapath} to ${datahadooppath} fail"
#fi

${HADOOP_HOME}/bin/hadoop fs -test -e ${JOB_OUTPUT}
if [ $? = 0 ]
then
    ${HADOOP_HOME}/bin/hadoop fs -rm -r ${JOB_OUTPUT}
fi

${HADOOP_HOME}/bin/hadoop \
    jar ${HADOOP_HOME}/share/hadoop/tools/lib/hadoop-streaming-2.7.1.jar \
    -D mapred.output.key.comparator.class=org.apache.hadoop.mapred.lib.KeyFieldBasedComparator \
    -D stream.num.map.output.key.fields=2 \
    -D num.key.fields.for.partition=1  \
    -D mapred.map.tasks=100 \
    -D mapred.reduce.tasks=80  \
    -D mapred.job.name="Lin.Cao Job:${job_name}" \
    -D mapred.text.key.comparator.options="-k1,1 -k2,2n" \
    -D stream.reduce.output.field.separator='|' \
    -D stream.num.reduce.output.key.fields=1  \
    -mapper "python index_mapper.py" \
    -reducer "python index_reducer.py" \
    -input ${JOB_INPUT}/post_data_month07 \
    -output ${JOB_OUTPUT} \
    -file ./index_mapper.py \
    -file ./index_reducer.py \
    -file ./stopword.txt \
    -file  ./jieba \
    -partitioner org.apache.hadoop.mapred.lib.KeyFieldBasedPartitioner\
    -jobconf mapreduce.reduce.java.opts=-Xmx1G \


    # -input ${JOB_INPUT}/question_data_0616 \
echo "job:${job_name} DONE"


# 本地生成索引
#name=`basename ${JOB_OUTPUT} `
#index_name=${name}_index
#mkdir $index_name
#${HADOOP_HOME}/bin/hadoop fs -copyToLocal  ${JOB_OUTPUT}/*  ${index_name}/
#cd ${index_name}/
#cat part* >> all_data
#awk '{split($2,arr,"|"); print $1, length(arr);}' all_data |sort -k2,2nr > all_data_term_tf
# dict 格式： term\tdf\tterm_id
#mkdir dict
#awk 'BEGIN{OFS="\t"} {if($2>10) print $1,$2,NR;}' all_data_term_tf > dict/worddict.dat
