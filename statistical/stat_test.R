require(lattice)

# Set the working directory
oldwd <- getwd()
setwd("~/Dropbox/Development/Masters/bmd/statistical/")

data1 <- read.csv("./data/eval/old_ves.csv")
data2 <- read.csv("./data/eval/ves_color.csv")

colnames = c('Area.Overlap', 'Area.Similarity', 'Overlap.Error', 'Sensivity', 'FPR')

for(i in colnames) {
        print(i)
        
        data <- data2[[i]]
        ref <- data1[[i]]
        
        ks <- ks.test(data, rnorm(length(data), mean=mean(data), sd=sd(data)))
        t <- t.test(data, ref)
        wilcox <- wilcox.test(data, ref)
        
        print(ks)
        print(t)
        print(wilcox)   
}

# colnames <- c('axon_area', 'axon_diameter', 'fiber_area', 'fiber_diameter', 'ratio_g');
# for (i in colnames){
#         
#         # Variables for the script, change if needed
#         file1_path <- paste("./data/clis_lar/", i, ".csv", sep="");
#         file2_path <- paste("./data/manual_lar/", i, ".csv", sep="");
#         
#         data1 <- read.csv(file1_path);
#         data2 <- read.csv(file2_path);
#         
#         print(i);
#         data1$x <- data1$x/sum(data1$x);
#         data2$x <- data2$x/sum(data2$x);
#         
#         data1_ks <- ks.test(data1$x, rnorm(length(data1$x), mean = mean(data1$x), sd = sd(data1$x)));
#         print('data1_ks');
#         print(data1_ks);
#         data2_ks <- ks.test(data2$x, rnorm(length(data2$x), mean = mean(data2$x), sd = sd(data2$x)));
#         print('data2_ks');
#         print(data2_ks);
#         
#         t <- t.test(data1$x, data2$x);
#        
#         wilcox <- wilcox.test(data1$x,data2$x);
#         print(t);
#         print(wilcox);
# }

setwd(oldwd)
