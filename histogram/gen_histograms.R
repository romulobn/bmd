require(lattice)

# Set the working directory
oldwd <- getwd()
setwd("~/Dropbox/Development/Masters/histogram/")

# Variables for the script, change if needed
type <- "insulin";
file_path <- paste( "diseasevscontrol/", type, "_data.csv", sep="")

# Load the data
data <- read.csv(file_path)
colnames(data)

# Plot histogram for Axon.Area
axon_area <- data$Axon.Area[data$Axon.Area < 60]
png(paste("./plot/", type,"/axon_area.png", sep=""), width = 480, height = 480, units = "px", bg = "transparent") 
histogram(axon_area, data, xlab="Axon Area", nint = 15, xlim=c(-10,60), ylim=c(0,30))
dev.off()
hist = hist(axon_area, breaks=seq(0,60,length.out=30))
write.csv(hist$counts, paste("./plot/", type,"/axon_area.csv", sep=""))

# Plot histogram for Fiber.Area
fiber_area <- data$Fiber.Area[data$Fiber.Area < 200]
png(paste("./plot/", type, "/fiber_area.png",sep=""), width = 480, height = 480, units = "px", bg = "transparent") 
histogram(fiber_area, data, xlab="Fiber Area", nint = 15, xlim=c(-10,200), ylim=c(0,40))
dev.off()
hist = hist(fiber_area, breaks=seq(0,200,length.out=30))
write.csv(hist$counts, paste("./plot/", type, "/fiber_area.csv",sep=""))

# Plot histogram for Axon.Diameter
axon_diameter <- data$Axon.Diameter[data$Axon.Diameter < 10]
png(paste("./plot/", type, "/axon_diameter.png",sep=""), width = 480, height = 480, units = "px", bg = "transparent") 
histogram(axon_diameter, data, xlab="Axon Diameter", nint = 15, xlim=c(-1,10), ylim=c(0,20))
dev.off()
hist = hist(axon_diameter, breaks=seq(0,10,length.out=30))
write.csv(hist$counts, paste("./plot/", type, "/axon_diameter.csv",sep=""))

# Plot histogram for Fiber.Diameter
fiber_diameter <- data$Fiber.Diameter[data$Fiber.Diameter < 15]
png(paste("./plot/", type, "/fiber_diameter.png", sep=""), width = 480, height = 480, units = "px", bg = "transparent") 
histogram(fiber_diameter, data, xlab="Fiber Diameter", nint = 15, xlim=c(-1,15), ylim=c(0,25))
dev.off()
hist = hist(fiber_diameter, breaks=seq(0,15,length.out=30))
write.csv(hist$counts, paste("./plot/", type, "/fiber_diameter.csv", sep=""))

# Plot histogram for Ratio.Diameter
ratio_g <- data$Ratio.G[data$Ratio.G <= 1]
png(paste("./plot/", type, "/ratio_g.png", sep=""), width = 480, height = 480, units = "px", bg = "transparent") 
histogram(ratio_g, data, xlab="Ratio G", nint = 15, xlim=c(-.1,1), ylim=c(0,20))
dev.off()
hist = hist(ratio_g, breaks=seq(0,1,length.out=30))
write.csv(hist$counts, paste("./plot/", type, "/ratio_g.csv", sep=""))

setwd(oldwd)

