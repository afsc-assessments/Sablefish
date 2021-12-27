###################################
# 2018 age request for sablefish, subsampling through R, 1/31/2018, D. hanselman
# Don't need anything for fishery ages, need otolith specimen file from Cara, or figure out how to query the LL database directly
#Updated version now does almost everything automatically with some checks added in 
#Uses AKFIN and AFSC databases
# For survey samples for 2015, the 
# For 2016 added BARCODE to fishery request per Jon Short's request and changed to OBSINT.DEBRIEFED_AGE_SQUAH_SP_TYPE to get the right stuff (the flattened table)
current<-2019
library(RODBC)
#### Connect to database for fishery age specimens, 
#conn<-odbcConnect(dsn="afsc",believeNRows=FALSE,uid="hanselmd",pwd="blubrd$$1234")
#conn<-odbcConnect(dsn="afsc",believeNRows=FALSE,uid="hanselmd",pwd="Highlife723!!!")
### switch to akfin in 2017
# change this to different year and different species if desired (currently 2011 and 203)
database_akfin="akfin" # use when at TSMRI
username_akfin=""
password_akfin=""
conn=odbcConnect(database_akfin,uid=username_akfin,pwd=password_akfin,believeNRows=FALSE)


##^^^^^^^^^^^^^^^^^^^^^
## Do it with flat table
#sqlAges <- "SELECT OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.HAUL_OFFLOAD_DATE HAUL_OFFLOAD_DATE, OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.VESSEL_CODE VESSEL_CODE, OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.CRUISE CRUISE, 
#OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.HAUL_OFFLOAD HAUL_OFFLOAD, OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.LATDD_START LATDD_START, OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.LONDD_START LONDD_START,
#OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.BOTTOM_DEPTH_FATHOMS BOTTOM_DEPTH_FATHOMS, OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.NMFS_AREA NMFS_AREA, OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.SPECIES SPECIES, OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.SEX SEX,
#OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.LENGTH LENGTH, OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.WEIGHT WEIGHT, OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.SPECIMEN_NUMBER SPECIMEN_NUMBER, OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.AGE AGE,OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.GEAR GEAR, OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.BARCODE BARCODE, OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.TYPE_1_OTOLITH OTOLITH, EXTRACT (year from OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.HAUL_OFFLOAD_DATE) YEAR FROM OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE WHERE YEAR = 2016 
#  AND  OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.LENGTH IS NOT NULL and (OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.NMFS_AREA < 659 and OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.NMFS_AREA <>649 )AND (OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.GEAR =6 OR OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.GEAR =8) AND  OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.SPECIES = 203 AND OBSINT.DEBRIEFED_AGE_SQUASH_SP_TYPE.TYPE_1_OTOLITH IS NOT NULL; "

sqlAges <- paste0("SELECT NORPAC.DEBRIEFED_AGE_FLAT_MV.HAUL_OFFLOAD_DATE HAUL_OFFLOAD_DATE, NORPAC.DEBRIEFED_AGE_FLAT_MV.VESSEL VESSEL, NORPAC.DEBRIEFED_AGE_FLAT_MV.CRUISE CRUISE, 
NORPAC.DEBRIEFED_AGE_FLAT_MV.HAUL_OFFLOAD HAUL_OFFLOAD, NORPAC.DEBRIEFED_AGE_FLAT_MV.LATDD_START LATDD_START, NORPAC.DEBRIEFED_AGE_FLAT_MV.LONDD_START LONDD_START,
NORPAC.DEBRIEFED_AGE_FLAT_MV.BOTTOM_DEPTH_FATHOMS BOTTOM_DEPTH_FATHOMS, NORPAC.DEBRIEFED_AGE_FLAT_MV.NMFS_AREA NMFS_AREA, NORPAC.DEBRIEFED_AGE_FLAT_MV.SPECIES SPECIES, NORPAC.DEBRIEFED_AGE_FLAT_MV.SEX SEX,
NORPAC.DEBRIEFED_AGE_FLAT_MV.LENGTH LENGTH, NORPAC.DEBRIEFED_AGE_FLAT_MV.WEIGHT WEIGHT, NORPAC.DEBRIEFED_AGE_FLAT_MV.SPECIMEN_NUMBER SPECIMEN_NUMBER, NORPAC.DEBRIEFED_AGE_FLAT_MV.AGE AGE,NORPAC.DEBRIEFED_AGE_FLAT_MV.GEAR GEAR, NORPAC.DEBRIEFED_AGE_FLAT_MV.BARCODE BARCODE, NORPAC.DEBRIEFED_AGE_FLAT_MV.TYPE_1_OTOLITH OTOLITH, EXTRACT (year from NORPAC.DEBRIEFED_AGE_FLAT_MV.HAUL_OFFLOAD_DATE) YEAR FROM NORPAC.DEBRIEFED_AGE_FLAT_MV
WHERE YEAR = ",current," AND  NORPAC.DEBRIEFED_AGE_FLAT_MV.LENGTH IS NOT NULL and (NORPAC.DEBRIEFED_AGE_FLAT_MV.NMFS_AREA < 659 and NORPAC.DEBRIEFED_AGE_FLAT_MV.NMFS_AREA <>649 )AND (NORPAC.DEBRIEFED_AGE_FLAT_MV.GEAR =6 OR NORPAC.DEBRIEFED_AGE_FLAT_MV.GEAR =8) AND  NORPAC.DEBRIEFED_AGE_FLAT_MV.SPECIES = 203 AND NORPAC.DEBRIEFED_AGE_FLAT_MV.TYPE_1_OTOLITH IS NOT NULL; ")

##-------------------------------------

## Clean out zero weights, no sex, and outliers
sable_fish_ages<-sqlQuery(conn,sqlAges) #get ages from ODBC connection
sfa<-sable_fish_ages
#sfa<-sable_fish_ages[sable_fish_ages$SPECIMEN_TYPE==1,] # smaller varname to work with, filter out other sample types
plot(sfa$LENGTH,sfa$WEIGHT) # take a look
sfa<-sfa[!is.na(sfa$LENGTH),] #get rid of NAs of length
sfa<-sfa[!is.na(sfa$WEIGHT),] #get rid of NAs of weight
sfa<-sfa[sfa$WEIGHT>0,] # Remove zero weights
sfa<-sfa[sfa$LENGTH>0,] # Remove zero lengths
sfa<-sfa[!is.na(sfa$LONDD_START),] # No location ages removed
sfa<-sfa[sfa$SEX!="U",] # Remove unsexed
sfa[sfa$LONDD>0,]$LONDD_START<-sfa[sfa$LONDD>0,]$LONDD_START-360 # make stuff west of the 180 line negative numbers
plot((sfa$LENGTH/(sfa$WEIGHT^0.3247))) # look at cube root (approximately linear), similar to allometric b of 3.08
# Alternatively could make more perfectly normal by using box-cox, e.g boxcox(lm(ssa$LENGTH~1/(ssa$WEIGHT)),lambda=seq(0.2,0.4,1/50))
ratio<-mean(sfa$LENGTH/(sfa$WEIGHT^0.3247)) #calculate the ratio
sdratio5<-5*sd(sfa$LENGTH/(sfa$WEIGHT^0.3247)) #5 standard deviations, 1000 samples, a result further is less than .003% probable)
upperout<-which((sfa$LENGTH/(sfa$WEIGHT^0.3247))>(ratio+sdratio5)) # calculate upper outliers (lengths are too long for weight)
lowerout<-which((sfa$LENGTH/(sfa$WEIGHT^0.3247))<(ratio-sdratio5)) # lower outliers (lengths are too short for weight)
if(length(lowerout)>0&length(upperout)>0) sfa<-sfa[-c(upperout,lowerout),] # get rid of outliers
if(length(lowerout)==0&length(upperout)>0) sfa<-sfa[-upperout,] 
if(length(lowerout)>0&length(upperout)==0) sfa<-sfa[-lowerout,] 
plot(sfa$LONDD_START,sfa$LATDD_START) # check distribution of locations

## Begin subsample by area
newareas<-read.csv("newareas.csv",header=TRUE) #get area names file
#newareas<-unique(areas) # transform to single areas
sfa$AREA_NAME<-newareas$AREA_NAME[match(sfa$NMFS_AREA,newareas$NMFS_AREA)] # use match to add AREA_NAME to age sample
table(sfa$AREA_NAME)
### Wow only 10 from the BS in 2015, what to do about that?
# target size is 200 per area, and 1200 total, if an area has less than 200, sample them all and adjust the rest upward
extra<-0
toosmall<-which(table(sfa$AREA_NAME)<200)
extra<-sum(round((200-table(sfa$AREA_NAME)[toosmall])/(6-length(toosmall))))
#if(rank(table(sfa$AREA_NAME)200)<0) extra<-round((min(table(sfa$AREA_NAME)-200)*-1)) #length(which((table(sfa$AREA_NAME)-200)>0)))
ss<-rep(200,6)+extra
ss[which((table(sfa$AREA_NAME)-200)<0)]<-table(sfa$AREA_NAME)[which((table(sfa$AREA_NAME)-200)<0)]
if(abs(sum(ss)-1200)>6) print("SHIT") else print("SWEET") #should be about 1200

x1<-sfa[sfa$AREA_NAME=="Aleutians",][sample(seq(1,length(sfa[sfa$AREA_NAME=="Aleutians",1])),ss[1],replace=FALSE),]
x2<-sfa[sfa$AREA_NAME=="Bering",][sample(seq(1,length(sfa[sfa$AREA_NAME=="Bering",1])),ss[2],replace=FALSE),]
x3<-sfa[sfa$AREA_NAME=="Western",][sample(seq(1,length(sfa[sfa$AREA_NAME=="Western",1])),ss[6],replace=FALSE),]
x4<-sfa[sfa$AREA_NAME=="Central",][sample(seq(1,length(sfa[sfa$AREA_NAME=="Central",1])),ss[3],replace=FALSE),]
x5<-sfa[sfa$AREA_NAME=="E Yakutat/Southeast",][sample(seq(1,length(sfa[sfa$AREA_NAME=="E Yakutat/Southeast",1])),ss[4],replace=FALSE),]
x6<-sfa[sfa$AREA_NAME=="W Yakutat",][sample(seq(1,length(sfa[sfa$AREA_NAME=="W Yakutat",1])),ss[5],replace=FALSE),]
finalsample<-rbind(x1,x2,x3,x4,x5,x6)

plot(finalsample$LONDD_START,finalsample$LATDD_START) # check distribution of locations
plot(finalsample$LENGTH,finalsample$WEIGHT) # take a look to make sure getting good size dist

write.csv(finalsample,"fishsample2019_barcode.csv") #write file to disk
odbcClose(conn)

##### Survey age subsample, shooting for 300 Aleutians or Bering Sea, 600 GOA slope, and 300 Goa Gullies, if not enough in BS or AI, then add to GOA Slope not Goa gullies
#current<-2018 # Enter current year
#setwd("C:/SA/AD2013/Sablefish/Data_files_for_assessment") # Current data file directory directory
#database_akfin="akfin" # use when at TSMRI
#database_akfin="CHINA" # use when at TSMRI
#database_akfin="CHINA" # use when at RO
#username_akfin="dhanselman"
#password_akfin="723Miller!"
#library(RODBC)

# Set up connection
# Use believeNRows=False for connecting to oracle driver for 64 bit machines
conn=odbcConnect(database_akfin,uid=username_akfin,pwd=password_akfin,believeNRows=FALSE)
sqlAges <- paste("SELECT * FROM AFSC.AGE_VIEW WHERE YEAR=",current,sep="")
surveyages<-sqlQuery(conn,sqlAges) #get ages from ODBC connection
sqlStations<-"SELECT * FROM AFSC.STATIONS_VIEW"
stations<-sqlQuery(conn,sqlStations)
odbcClose(conn)
#surveyages<-read.csv("age_view.csv",header=TRUE,skip=5) #old way
## Clean out zero weights, no sex, and outliers
### read in cara maturity data
#mat<-read.csv("mat_specs.csv",header=T, stringsAsFactors = FALSE)
#ab<-(mat[which(mat[,15]>0),11]) ## set up vector of which specimens are maturity samples
#spnums<-mat[ab,11]
ssa<-surveyages # smaller varname
#names(ssa)[3]<-"STATION"
names(ssa)[6]<-"LATDD_START"
names(ssa)[7]<-"LONDD_START"
#names(ssa)[20]<-"LENGTH"
#names(ssa)[21]<-"WEIGHT"
#names(ssa)[15]<-"SEX"
plot(ssa$LONDD_START,ssa$LATDD_START) # check distribution of locations


plot(ssa$LENGTH,ssa$WEIGHT) # take a look
ssa<-ssa[!is.na(ssa$LENGTH),] #get rid of NAs of length
ssa<-ssa[!is.na(ssa$WEIGHT),] #get rid of NAs of length
ssa<-ssa[ssa$WEIGHT>0,] # Remove zero weights
ssa<-ssa[ssa$LENGTH>0,] # Remove zero weights
ssa<-ssa[ssa$SEX!=3,] #get rid of unsexed fish
ssa<-ssa[is.na(ssa$AGE_NOTES),] # Why age broken otoliths? Doesn't work with AKFIN, no notes online

plot((ssa$LENGTH/(ssa$WEIGHT)^0.3247)) # look at cube root (approximately linear), similar to allometric b of 3.08
ratio<-mean(ssa$LENGTH/(ssa$WEIGHT)^0.3247) #calculate the ratio
sdratio5<-5*sd(ssa$LENGTH/(ssa$WEIGHT)^0.3247) #5 standard deviations, 1000 samples, a result further is less than .003% probable
upperout<-which(ssa$LENGTH/(ssa$WEIGHT)^0.3247>(ratio+sdratio5)) # # calculate upper outliers (lengths are too long for weight)
lowerout<-which(ssa$LENGTH/(ssa$WEIGHT)^0.3247<(ratio-sdratio5)) # lower outliers (lengths are too short for weight)
if(length(lowerout)>0&length(upperout)>0) ssa<-ssa[-c(upperout,lowerout),] # get rid of outliers
if(length(lowerout)==0&length(upperout)>0) ssa<-ssa[-upperout,] 
if(length(lowerout)>0&length(upperout)==0) ssa<-ssa[-lowerout,] 


## Begin subsample
stationareas<-read.csv("stationareas.csv",header=TRUE) #get area names file
#locations<-read.csv("c://sa//stationlocations.csv",header=TRUE) # get station locations. don't need now
stareas<-unique(stationareas) # transform to single areas
stations<-stations[stations$ACTIVE==1,]
ssa$AREA_NAME<-stations$REGION[match(ssa$STATION,stations$STATION_NUMBER)] # use match to add AREA_NAME to age sample
ssa$HAB<-stations$HABITAT_TYPE[match(ssa$STATION,stations$STATION_NUMBER)] # use match to add AREA_NAME to age sample

ssa$AREA_NAME<-as.character(ssa$AREA_NAME)
ssa$HAB<-as.character(ssa$HAB)

ssa[which(ssa$HAB!="Upper continental slope"),29]<-"GOA Gullies"
#ssa$HAB<-as.factor(ssa$HAB)
#ssa$AREA_NAME<-as.factor(ssa$AREA_NAME)

table(ssa$AREA_NAME)
# target size is 300 per area, and 1200 total, if an area has less than 200, sample them all and adjust the rest upward
extra<-0
if(min(table(ssa$AREA_NAME)-300)<0) extra<-round((min(table(ssa$AREA_NAME)-300)*-1)/length(which((table(ssa$AREA_NAME)-300)>0)))
ss2<-c(300,300,600)
if(min(table(ssa$AREA_NAME)-ss2)<0) {
  ss<-ss2+extra
  ss[which(table(ssa$AREA_NAME)-ss<0&ss>300)]<-table(ssa$AREA_NAME)[which(table(ssa$AREA_NAME)-ss<0&ss>300)]
  ss[3]<-ss[3]-(ss[which(table(ssa$AREA_NAME)-ss<1&ss>300)]-300-extra)}
if(min(table(ssa$AREA_NAME)-ss2)>0) ss<-ss2
#ss[which((table(ssa$AREA_NAME)-300)<0)]<-table(ssa$AREA_NAME)[which((table(ssa$AREA_NAME)-300)<0)]
if(abs(sum(ss)-1200)>6) print("SHIT") else print("SWEET") #should be about 1200
x1<-ssa[which(ssa$AREA_NAME=="GOA Gullies"),][sample(seq(1,length(ssa[which(ssa$AREA_NAME=="GOA Gullies"),1])),ss[2],replace=FALSE),] # Goal is 300
if(ceiling(ssa$YEAR[1]/2)/round(ssa$YEAR[1]/2)>1){
x2<-ssa[which(ssa$AREA_NAME=="Eastern  Bering Sea"),][sample(seq(1,length(ssa[which(ssa$AREA_NAME=="Eastern  Bering Sea"),1])),ss[1],replace=FALSE),]}
if(ceiling(ssa$YEAR[1]/2)/round(ssa$YEAR[1]/2)==1) 
  {x2<-ssa[which(ssa$AREA_NAME=="Aleutian Islands"),][sample(seq(1,length(ssa[which(ssa$AREA_NAME=="Aleutian Islands"),1])),ss[1],replace=FALSE),]}
x3<-ssa[which(ssa$AREA_NAME=="Gulf of Alaska"),][sample(seq(1,length(ssa[which(ssa$AREA_NAME=="Gulf of Alaska"),1])),ss[3],replace=FALSE),] #Goal is 600"
finalsample<-rbind(x1,x2,x3)
#finalsample$LAT<-locations$lat[match(finalsample$STATION,locations$Station)]
#finalsample$LON<-locations$Lon[match(finalsample$STATION,locations$Station)]
plot(finalsample$LONDD_START,finalsample$LATDD_START) # check distribution of locations
plot(finalsample$LENGTH,finalsample$WEIGHT) # check distribution of length weight
table(finalsample$AREA)
summary(finalsample)
write.csv(finalsample,"survsample2019.csv") #write file to disk

