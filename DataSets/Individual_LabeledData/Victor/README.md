# Tutorial: 
1. Create a anaconda environment:
    a. Open anaconda prompt -> type: conda create --name <env_name> python=<version>
    b. activate environment -> type: conda activate <env_name>
    b. type: pip install ultralytics
2. Check pytorch version and cuda:
    a. type: python -> import torch -> torch.cuda.is_available() -> **should be False**
    b. Check version: type: torch.__version__
3. Go to pytorch.com install latest pytorch with the corresponding version
4. Create data.yaml (see mine for format)
5. Create three folders: train, val, and test. Each of them needs to have an image folder and labels folder
6. Run yolo model=yolov8l.pt mode=train task=detect data=data.yaml epochs=XXX batch=YYY in anaconda prompt 