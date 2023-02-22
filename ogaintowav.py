from pydub import AudioSegment

# Specify the path to the OGA file
input_path = "Assets/sound/Ci1playerhit.oga"

# Load the audio file using pydub
audio = AudioSegment.from_file(input_path, format="oga")

# Specify the output path and file name
output_path = "Assets/sound/Ci1playerhit.oga"

# Export the audio to the WAV format
audio.export(output_path, format="wav")
