FROM python:3.9-slim

WORKDIR /app

COPY requirements.txt requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

COPY aes_128.py aes_128.py

CMD ["python", "aes_128.py"]