delete('output_video.avi');
files=dir;
files=files(~ismember({files.name},{'.','..'}));


video_object = VideoWriter('output_video.avi');
video_object.FrameRate = 5;
open(video_object);

f = figure; hold on;
for i=1:length(files)
    frame = load(files(i).name);
    imagesc(frame); colormap(gray); axis off;
    writeVideo(video_object, getframe(f));
end

close(video_object);