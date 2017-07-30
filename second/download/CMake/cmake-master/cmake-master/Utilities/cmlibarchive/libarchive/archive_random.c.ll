; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_random.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.arc4_stream = type { i8, i8, [256 x i8] }
%struct.anon = type { %struct.timeval, i32, [128 x i8] }
%struct.timeval = type { i64, i64 }
%struct.timezone = type { i32, i32 }

@arc4_count = internal global i32 0, align 4
@rs_initialized = internal global i32 0, align 4
@arc4_stir_pid = internal global i32 0, align 4
@.str = private unnamed_addr constant [13 x i8] c"/dev/urandom\00", align 1
@rs = internal global %struct.arc4_stream zeroinitializer, align 1

; Function Attrs: nounwind uwtable
define i32 @archive_random(i8* %buf, i64 %nbytes) #0 !dbg !11 {
entry:
  %buf.addr = alloca i8*, align 8
  %nbytes.addr = alloca i64, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !53, metadata !54), !dbg !55
  store i64 %nbytes, i64* %nbytes.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %nbytes.addr, metadata !56, metadata !54), !dbg !57
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !58
  %1 = load i64, i64* %nbytes.addr, align 8, !dbg !59
  call void @arc4random_buf(i8* %0, i64 %1), !dbg !60
  ret i32 0, !dbg !61
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal void @arc4random_buf(i8* %_buf, i64 %n) #0 !dbg !19 {
entry:
  %_buf.addr = alloca i8*, align 8
  %n.addr = alloca i64, align 8
  %buf = alloca i8*, align 8
  store i8* %_buf, i8** %_buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %_buf.addr, metadata !62, metadata !54), !dbg !63
  store i64 %n, i64* %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %n.addr, metadata !64, metadata !54), !dbg !65
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !66, metadata !54), !dbg !67
  %0 = load i8*, i8** %_buf.addr, align 8, !dbg !68
  store i8* %0, i8** %buf, align 8, !dbg !67
  call void @arc4_stir_if_needed(), !dbg !69
  br label %while.cond, !dbg !70

while.cond:                                       ; preds = %if.end, %entry
  %1 = load i64, i64* %n.addr, align 8, !dbg !71
  %dec = add i64 %1, -1, !dbg !71
  store i64 %dec, i64* %n.addr, align 8, !dbg !71
  %tobool = icmp ne i64 %1, 0, !dbg !73
  br i1 %tobool, label %while.body, label %while.end, !dbg !73

while.body:                                       ; preds = %while.cond
  %2 = load i32, i32* @arc4_count, align 4, !dbg !74
  %dec1 = add nsw i32 %2, -1, !dbg !74
  store i32 %dec1, i32* @arc4_count, align 4, !dbg !74
  %cmp = icmp sle i32 %dec1, 0, !dbg !77
  br i1 %cmp, label %if.then, label %if.end, !dbg !78

if.then:                                          ; preds = %while.body
  call void @arc4_stir(), !dbg !79
  br label %if.end, !dbg !79

if.end:                                           ; preds = %if.then, %while.body
  %call = call zeroext i8 @arc4_getbyte(), !dbg !80
  %3 = load i64, i64* %n.addr, align 8, !dbg !81
  %4 = load i8*, i8** %buf, align 8, !dbg !82
  %arrayidx = getelementptr inbounds i8, i8* %4, i64 %3, !dbg !82
  store i8 %call, i8* %arrayidx, align 1, !dbg !83
  br label %while.cond, !dbg !84

while.end:                                        ; preds = %while.cond
  ret void, !dbg !86
}

; Function Attrs: nounwind uwtable
define internal void @arc4_stir_if_needed() #0 !dbg !22 {
entry:
  %pid = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %pid, metadata !87, metadata !54), !dbg !88
  %call = call i32 @getpid() #5, !dbg !89
  store i32 %call, i32* %pid, align 4, !dbg !88
  %0 = load i32, i32* @arc4_count, align 4, !dbg !90
  %cmp = icmp sle i32 %0, 0, !dbg !92
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !93

lor.lhs.false:                                    ; preds = %entry
  %1 = load i32, i32* @rs_initialized, align 4, !dbg !94
  %tobool = icmp ne i32 %1, 0, !dbg !94
  br i1 %tobool, label %lor.lhs.false1, label %if.then, !dbg !96

lor.lhs.false1:                                   ; preds = %lor.lhs.false
  %2 = load i32, i32* @arc4_stir_pid, align 4, !dbg !97
  %3 = load i32, i32* %pid, align 4, !dbg !99
  %cmp2 = icmp ne i32 %2, %3, !dbg !100
  br i1 %cmp2, label %if.then, label %if.end, !dbg !101

if.then:                                          ; preds = %lor.lhs.false1, %lor.lhs.false, %entry
  %4 = load i32, i32* %pid, align 4, !dbg !102
  store i32 %4, i32* @arc4_stir_pid, align 4, !dbg !104
  call void @arc4_stir(), !dbg !105
  br label %if.end, !dbg !106

if.end:                                           ; preds = %if.then, %lor.lhs.false1
  ret void, !dbg !107
}

; Function Attrs: nounwind uwtable
define internal void @arc4_stir() #0 !dbg !25 {
entry:
  %done = alloca i32, align 4
  %fd = alloca i32, align 4
  %i = alloca i32, align 4
  %rdat = alloca %struct.anon, align 8
  call void @llvm.dbg.declare(metadata i32* %done, metadata !108, metadata !54), !dbg !109
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !110, metadata !54), !dbg !111
  call void @llvm.dbg.declare(metadata i32* %i, metadata !112, metadata !54), !dbg !113
  call void @llvm.dbg.declare(metadata %struct.anon* %rdat, metadata !114, metadata !54), !dbg !131
  %0 = load i32, i32* @rs_initialized, align 4, !dbg !132
  %tobool = icmp ne i32 %0, 0, !dbg !132
  br i1 %tobool, label %if.end, label %if.then, !dbg !134

if.then:                                          ; preds = %entry
  call void @arc4_init(), !dbg !135
  store i32 1, i32* @rs_initialized, align 4, !dbg !137
  br label %if.end, !dbg !138

if.end:                                           ; preds = %if.then, %entry
  store i32 0, i32* %done, align 4, !dbg !139
  %call = call i32 (i8*, i32, ...) @open(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str, i32 0, i32 0), i32 524288, i32 0), !dbg !140
  store i32 %call, i32* %fd, align 4, !dbg !141
  %1 = load i32, i32* %fd, align 4, !dbg !142
  %cmp = icmp sge i32 %1, 0, !dbg !144
  br i1 %cmp, label %if.then1, label %if.end7, !dbg !145

if.then1:                                         ; preds = %if.end
  %2 = load i32, i32* %fd, align 4, !dbg !146
  %3 = bitcast %struct.anon* %rdat to i8*, !dbg !149
  %call2 = call i64 @read(i32 %2, i8* %3, i64 128), !dbg !150
  %cmp3 = icmp eq i64 %call2, 128, !dbg !151
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !152

if.then4:                                         ; preds = %if.then1
  store i32 1, i32* %done, align 4, !dbg !153
  br label %if.end5, !dbg !154

if.end5:                                          ; preds = %if.then4, %if.then1
  %4 = load i32, i32* %fd, align 4, !dbg !155
  %call6 = call i32 @close(i32 %4), !dbg !156
  br label %if.end7, !dbg !157

if.end7:                                          ; preds = %if.end5, %if.end
  %5 = load i32, i32* %done, align 4, !dbg !158
  %tobool8 = icmp ne i32 %5, 0, !dbg !158
  br i1 %tobool8, label %if.end12, label %if.then9, !dbg !160

if.then9:                                         ; preds = %if.end7
  %tv = getelementptr inbounds %struct.anon, %struct.anon* %rdat, i32 0, i32 0, !dbg !161
  %call10 = call i32 @gettimeofday(%struct.timeval* %tv, %struct.timezone* null) #5, !dbg !163
  %call11 = call i32 @getpid() #5, !dbg !164
  %pid = getelementptr inbounds %struct.anon, %struct.anon* %rdat, i32 0, i32 1, !dbg !165
  store i32 %call11, i32* %pid, align 8, !dbg !166
  br label %if.end12, !dbg !167

if.end12:                                         ; preds = %if.then9, %if.end7
  %6 = bitcast %struct.anon* %rdat to i8*, !dbg !168
  call void @arc4_addrandom(i8* %6, i32 128), !dbg !169
  store i32 0, i32* %i, align 4, !dbg !170
  br label %for.cond, !dbg !172

for.cond:                                         ; preds = %for.inc, %if.end12
  %7 = load i32, i32* %i, align 4, !dbg !173
  %cmp13 = icmp slt i32 %7, 3072, !dbg !176
  br i1 %cmp13, label %for.body, label %for.end, !dbg !177

for.body:                                         ; preds = %for.cond
  %call14 = call zeroext i8 @arc4_getbyte(), !dbg !178
  br label %for.inc, !dbg !179

for.inc:                                          ; preds = %for.body
  %8 = load i32, i32* %i, align 4, !dbg !180
  %inc = add nsw i32 %8, 1, !dbg !180
  store i32 %inc, i32* %i, align 4, !dbg !180
  br label %for.cond, !dbg !182

for.end:                                          ; preds = %for.cond
  store i32 1600000, i32* @arc4_count, align 4, !dbg !183
  ret void, !dbg !184
}

; Function Attrs: inlinehint nounwind uwtable
define internal zeroext i8 @arc4_getbyte() #2 !dbg !30 {
entry:
  %si = alloca i8, align 1
  %sj = alloca i8, align 1
  call void @llvm.dbg.declare(metadata i8* %si, metadata !185, metadata !54), !dbg !186
  call void @llvm.dbg.declare(metadata i8* %sj, metadata !187, metadata !54), !dbg !188
  %0 = load i8, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 0), align 1, !dbg !189
  %conv = zext i8 %0 to i32, !dbg !190
  %add = add nsw i32 %conv, 1, !dbg !191
  %conv1 = trunc i32 %add to i8, !dbg !192
  store i8 %conv1, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 0), align 1, !dbg !193
  %1 = load i8, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 0), align 1, !dbg !194
  %idxprom = zext i8 %1 to i64, !dbg !195
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 2), i64 0, i64 %idxprom, !dbg !195
  %2 = load i8, i8* %arrayidx, align 1, !dbg !195
  store i8 %2, i8* %si, align 1, !dbg !196
  %3 = load i8, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 1), align 1, !dbg !197
  %conv2 = zext i8 %3 to i32, !dbg !198
  %4 = load i8, i8* %si, align 1, !dbg !199
  %conv3 = zext i8 %4 to i32, !dbg !199
  %add4 = add nsw i32 %conv2, %conv3, !dbg !200
  %conv5 = trunc i32 %add4 to i8, !dbg !201
  store i8 %conv5, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 1), align 1, !dbg !202
  %5 = load i8, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 1), align 1, !dbg !203
  %idxprom6 = zext i8 %5 to i64, !dbg !204
  %arrayidx7 = getelementptr inbounds [256 x i8], [256 x i8]* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 2), i64 0, i64 %idxprom6, !dbg !204
  %6 = load i8, i8* %arrayidx7, align 1, !dbg !204
  store i8 %6, i8* %sj, align 1, !dbg !205
  %7 = load i8, i8* %sj, align 1, !dbg !206
  %8 = load i8, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 0), align 1, !dbg !207
  %idxprom8 = zext i8 %8 to i64, !dbg !208
  %arrayidx9 = getelementptr inbounds [256 x i8], [256 x i8]* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 2), i64 0, i64 %idxprom8, !dbg !208
  store i8 %7, i8* %arrayidx9, align 1, !dbg !209
  %9 = load i8, i8* %si, align 1, !dbg !210
  %10 = load i8, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 1), align 1, !dbg !211
  %idxprom10 = zext i8 %10 to i64, !dbg !212
  %arrayidx11 = getelementptr inbounds [256 x i8], [256 x i8]* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 2), i64 0, i64 %idxprom10, !dbg !212
  store i8 %9, i8* %arrayidx11, align 1, !dbg !213
  %11 = load i8, i8* %si, align 1, !dbg !214
  %conv12 = zext i8 %11 to i32, !dbg !214
  %12 = load i8, i8* %sj, align 1, !dbg !215
  %conv13 = zext i8 %12 to i32, !dbg !215
  %add14 = add nsw i32 %conv12, %conv13, !dbg !216
  %and = and i32 %add14, 255, !dbg !217
  %idxprom15 = sext i32 %and to i64, !dbg !218
  %arrayidx16 = getelementptr inbounds [256 x i8], [256 x i8]* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 2), i64 0, i64 %idxprom15, !dbg !218
  %13 = load i8, i8* %arrayidx16, align 1, !dbg !218
  ret i8 %13, !dbg !219
}

; Function Attrs: nounwind
declare i32 @getpid() #3

; Function Attrs: inlinehint nounwind uwtable
define internal void @arc4_init() #2 !dbg !26 {
entry:
  %n = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %n, metadata !220, metadata !54), !dbg !221
  store i32 0, i32* %n, align 4, !dbg !222
  br label %for.cond, !dbg !224

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %n, align 4, !dbg !225
  %cmp = icmp slt i32 %0, 256, !dbg !228
  br i1 %cmp, label %for.body, label %for.end, !dbg !229

for.body:                                         ; preds = %for.cond
  %1 = load i32, i32* %n, align 4, !dbg !230
  %conv = trunc i32 %1 to i8, !dbg !230
  %2 = load i32, i32* %n, align 4, !dbg !231
  %idxprom = sext i32 %2 to i64, !dbg !232
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 2), i64 0, i64 %idxprom, !dbg !232
  store i8 %conv, i8* %arrayidx, align 1, !dbg !233
  br label %for.inc, !dbg !232

for.inc:                                          ; preds = %for.body
  %3 = load i32, i32* %n, align 4, !dbg !234
  %inc = add nsw i32 %3, 1, !dbg !234
  store i32 %inc, i32* %n, align 4, !dbg !234
  br label %for.cond, !dbg !236

for.end:                                          ; preds = %for.cond
  store i8 0, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 0), align 1, !dbg !237
  store i8 0, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 1), align 1, !dbg !238
  ret void, !dbg !239
}

declare i32 @open(i8*, i32, ...) #4

declare i64 @read(i32, i8*, i64) #4

declare i32 @close(i32) #4

; Function Attrs: nounwind
declare i32 @gettimeofday(%struct.timeval*, %struct.timezone*) #3

; Function Attrs: inlinehint nounwind uwtable
define internal void @arc4_addrandom(i8* %dat, i32 %datlen) #2 !dbg !27 {
entry:
  %dat.addr = alloca i8*, align 8
  %datlen.addr = alloca i32, align 4
  %n = alloca i32, align 4
  %si = alloca i8, align 1
  store i8* %dat, i8** %dat.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dat.addr, metadata !240, metadata !54), !dbg !241
  store i32 %datlen, i32* %datlen.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %datlen.addr, metadata !242, metadata !54), !dbg !243
  call void @llvm.dbg.declare(metadata i32* %n, metadata !244, metadata !54), !dbg !245
  call void @llvm.dbg.declare(metadata i8* %si, metadata !246, metadata !54), !dbg !247
  %0 = load i8, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 0), align 1, !dbg !248
  %dec = add i8 %0, -1, !dbg !248
  store i8 %dec, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 0), align 1, !dbg !248
  store i32 0, i32* %n, align 4, !dbg !249
  br label %for.cond, !dbg !251

for.cond:                                         ; preds = %for.inc, %entry
  %1 = load i32, i32* %n, align 4, !dbg !252
  %cmp = icmp slt i32 %1, 256, !dbg !255
  br i1 %cmp, label %for.body, label %for.end, !dbg !256

for.body:                                         ; preds = %for.cond
  %2 = load i8, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 0), align 1, !dbg !257
  %conv = zext i8 %2 to i32, !dbg !259
  %add = add nsw i32 %conv, 1, !dbg !260
  %conv1 = trunc i32 %add to i8, !dbg !261
  store i8 %conv1, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 0), align 1, !dbg !262
  %3 = load i8, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 0), align 1, !dbg !263
  %idxprom = zext i8 %3 to i64, !dbg !264
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 2), i64 0, i64 %idxprom, !dbg !264
  %4 = load i8, i8* %arrayidx, align 1, !dbg !264
  store i8 %4, i8* %si, align 1, !dbg !265
  %5 = load i8, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 1), align 1, !dbg !266
  %conv2 = zext i8 %5 to i32, !dbg !267
  %6 = load i8, i8* %si, align 1, !dbg !268
  %conv3 = zext i8 %6 to i32, !dbg !268
  %add4 = add nsw i32 %conv2, %conv3, !dbg !269
  %7 = load i32, i32* %n, align 4, !dbg !270
  %8 = load i32, i32* %datlen.addr, align 4, !dbg !271
  %rem = srem i32 %7, %8, !dbg !272
  %idxprom5 = sext i32 %rem to i64, !dbg !273
  %9 = load i8*, i8** %dat.addr, align 8, !dbg !273
  %arrayidx6 = getelementptr inbounds i8, i8* %9, i64 %idxprom5, !dbg !273
  %10 = load i8, i8* %arrayidx6, align 1, !dbg !273
  %conv7 = zext i8 %10 to i32, !dbg !273
  %add8 = add nsw i32 %add4, %conv7, !dbg !274
  %conv9 = trunc i32 %add8 to i8, !dbg !275
  store i8 %conv9, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 1), align 1, !dbg !276
  %11 = load i8, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 1), align 1, !dbg !277
  %idxprom10 = zext i8 %11 to i64, !dbg !278
  %arrayidx11 = getelementptr inbounds [256 x i8], [256 x i8]* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 2), i64 0, i64 %idxprom10, !dbg !278
  %12 = load i8, i8* %arrayidx11, align 1, !dbg !278
  %13 = load i8, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 0), align 1, !dbg !279
  %idxprom12 = zext i8 %13 to i64, !dbg !280
  %arrayidx13 = getelementptr inbounds [256 x i8], [256 x i8]* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 2), i64 0, i64 %idxprom12, !dbg !280
  store i8 %12, i8* %arrayidx13, align 1, !dbg !281
  %14 = load i8, i8* %si, align 1, !dbg !282
  %15 = load i8, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 1), align 1, !dbg !283
  %idxprom14 = zext i8 %15 to i64, !dbg !284
  %arrayidx15 = getelementptr inbounds [256 x i8], [256 x i8]* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 2), i64 0, i64 %idxprom14, !dbg !284
  store i8 %14, i8* %arrayidx15, align 1, !dbg !285
  br label %for.inc, !dbg !286

for.inc:                                          ; preds = %for.body
  %16 = load i32, i32* %n, align 4, !dbg !287
  %inc = add nsw i32 %16, 1, !dbg !287
  store i32 %inc, i32* %n, align 4, !dbg !287
  br label %for.cond, !dbg !289

for.end:                                          ; preds = %for.cond
  %17 = load i8, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 0), align 1, !dbg !290
  store i8 %17, i8* getelementptr inbounds (%struct.arc4_stream, %struct.arc4_stream* @rs, i32 0, i32 1), align 1, !dbg !291
  ret void, !dbg !292
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!50, !51}
!llvm.ident = !{!52}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !10, globals: !35)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_random.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_typedef, name: "u_char", file: !6, line: 33, baseType: !7)
!6 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !DIDerivedType(tag: DW_TAG_typedef, name: "__u_char", file: !8, line: 30, baseType: !9)
!8 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!9 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!10 = !{!11, !19, !22, !25, !26, !27, !30}
!11 = distinct !DISubprogram(name: "archive_random", scope: !1, file: !1, line: 75, type: !12, isLocal: false, isDefinition: true, scopeLine: 76, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!12 = !DISubroutineType(types: !13)
!13 = !{!14, !15, !16}
!14 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!15 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !17, line: 62, baseType: !18)
!17 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!18 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!19 = distinct !DISubprogram(name: "arc4random_buf", scope: !1, file: !1, line: 256, type: !20, isLocal: true, isDefinition: true, scopeLine: 257, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!20 = !DISubroutineType(types: !21)
!21 = !{null, !15, !16}
!22 = distinct !DISubprogram(name: "arc4_stir_if_needed", scope: !1, file: !1, line: 231, type: !23, isLocal: true, isDefinition: true, scopeLine: 232, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!23 = !DISubroutineType(types: !24)
!24 = !{null}
!25 = distinct !DISubprogram(name: "arc4_stir", scope: !1, file: !1, line: 193, type: !23, isLocal: true, isDefinition: true, scopeLine: 194, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!26 = distinct !DISubprogram(name: "arc4_init", scope: !1, file: !1, line: 165, type: !23, isLocal: true, isDefinition: true, scopeLine: 166, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!27 = distinct !DISubprogram(name: "arc4_addrandom", scope: !1, file: !1, line: 176, type: !28, isLocal: true, isDefinition: true, scopeLine: 177, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!28 = !DISubroutineType(types: !29)
!29 = !{null, !4, !14}
!30 = distinct !DISubprogram(name: "arc4_getbyte", scope: !1, file: !1, line: 242, type: !31, isLocal: true, isDefinition: true, scopeLine: 243, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!31 = !DISubroutineType(types: !32)
!32 = !{!33}
!33 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !34, line: 48, baseType: !9)
!34 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!35 = !{!36, !37, !40, !41}
!36 = !DIGlobalVariable(name: "rs_initialized", scope: !0, file: !1, line: 156, type: !14, isLocal: true, isDefinition: true, variable: i32* @rs_initialized)
!37 = !DIGlobalVariable(name: "arc4_stir_pid", scope: !0, file: !1, line: 158, type: !38, isLocal: true, isDefinition: true, variable: i32* @arc4_stir_pid)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "pid_t", file: !6, line: 98, baseType: !39)
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pid_t", file: !8, line: 133, baseType: !14)
!40 = !DIGlobalVariable(name: "arc4_count", scope: !0, file: !1, line: 159, type: !14, isLocal: true, isDefinition: true, variable: i32* @arc4_count)
!41 = !DIGlobalVariable(name: "rs", scope: !0, file: !1, line: 157, type: !42, isLocal: true, isDefinition: true, variable: %struct.arc4_stream* @rs)
!42 = !DICompositeType(tag: DW_TAG_structure_type, name: "arc4_stream", file: !1, line: 139, size: 2064, align: 8, elements: !43)
!43 = !{!44, !45, !46}
!44 = !DIDerivedType(tag: DW_TAG_member, name: "i", scope: !42, file: !1, line: 140, baseType: !33, size: 8, align: 8)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "j", scope: !42, file: !1, line: 141, baseType: !33, size: 8, align: 8, offset: 8)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !42, file: !1, line: 142, baseType: !47, size: 2048, align: 8, offset: 16)
!47 = !DICompositeType(tag: DW_TAG_array_type, baseType: !33, size: 2048, align: 8, elements: !48)
!48 = !{!49}
!49 = !DISubrange(count: 256)
!50 = !{i32 2, !"Dwarf Version", i32 4}
!51 = !{i32 2, !"Debug Info Version", i32 3}
!52 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!53 = !DILocalVariable(name: "buf", arg: 1, scope: !11, file: !1, line: 75, type: !15)
!54 = !DIExpression()
!55 = !DILocation(line: 75, column: 22, scope: !11)
!56 = !DILocalVariable(name: "nbytes", arg: 2, scope: !11, file: !1, line: 75, type: !16)
!57 = !DILocation(line: 75, column: 34, scope: !11)
!58 = !DILocation(line: 96, column: 17, scope: !11)
!59 = !DILocation(line: 96, column: 22, scope: !11)
!60 = !DILocation(line: 96, column: 2, scope: !11)
!61 = !DILocation(line: 97, column: 2, scope: !11)
!62 = !DILocalVariable(name: "_buf", arg: 1, scope: !19, file: !1, line: 256, type: !15)
!63 = !DILocation(line: 256, column: 22, scope: !19)
!64 = !DILocalVariable(name: "n", arg: 2, scope: !19, file: !1, line: 256, type: !16)
!65 = !DILocation(line: 256, column: 35, scope: !19)
!66 = !DILocalVariable(name: "buf", scope: !19, file: !1, line: 258, type: !4)
!67 = !DILocation(line: 258, column: 10, scope: !19)
!68 = !DILocation(line: 258, column: 26, scope: !19)
!69 = !DILocation(line: 260, column: 2, scope: !19)
!70 = !DILocation(line: 261, column: 2, scope: !19)
!71 = !DILocation(line: 261, column: 10, scope: !72)
!72 = !DILexicalBlockFile(scope: !19, file: !1, discriminator: 1)
!73 = !DILocation(line: 261, column: 2, scope: !72)
!74 = !DILocation(line: 262, column: 7, scope: !75)
!75 = distinct !DILexicalBlock(scope: !76, file: !1, line: 262, column: 7)
!76 = distinct !DILexicalBlock(scope: !19, file: !1, line: 261, column: 14)
!77 = !DILocation(line: 262, column: 20, scope: !75)
!78 = !DILocation(line: 262, column: 7, scope: !76)
!79 = !DILocation(line: 263, column: 4, scope: !75)
!80 = !DILocation(line: 264, column: 12, scope: !76)
!81 = !DILocation(line: 264, column: 7, scope: !76)
!82 = !DILocation(line: 264, column: 3, scope: !76)
!83 = !DILocation(line: 264, column: 10, scope: !76)
!84 = !DILocation(line: 261, column: 2, scope: !85)
!85 = !DILexicalBlockFile(scope: !19, file: !1, discriminator: 2)
!86 = !DILocation(line: 267, column: 1, scope: !19)
!87 = !DILocalVariable(name: "pid", scope: !22, file: !1, line: 233, type: !38)
!88 = !DILocation(line: 233, column: 8, scope: !22)
!89 = !DILocation(line: 233, column: 14, scope: !22)
!90 = !DILocation(line: 235, column: 6, scope: !91)
!91 = distinct !DILexicalBlock(scope: !22, file: !1, line: 235, column: 6)
!92 = !DILocation(line: 235, column: 17, scope: !91)
!93 = !DILocation(line: 235, column: 22, scope: !91)
!94 = !DILocation(line: 235, column: 26, scope: !95)
!95 = !DILexicalBlockFile(scope: !91, file: !1, discriminator: 1)
!96 = !DILocation(line: 235, column: 41, scope: !95)
!97 = !DILocation(line: 235, column: 44, scope: !98)
!98 = !DILexicalBlockFile(scope: !91, file: !1, discriminator: 2)
!99 = !DILocation(line: 235, column: 61, scope: !98)
!100 = !DILocation(line: 235, column: 58, scope: !98)
!101 = !DILocation(line: 235, column: 6, scope: !98)
!102 = !DILocation(line: 236, column: 19, scope: !103)
!103 = distinct !DILexicalBlock(scope: !91, file: !1, line: 235, column: 66)
!104 = !DILocation(line: 236, column: 17, scope: !103)
!105 = !DILocation(line: 237, column: 3, scope: !103)
!106 = !DILocation(line: 238, column: 2, scope: !103)
!107 = !DILocation(line: 239, column: 1, scope: !22)
!108 = !DILocalVariable(name: "done", scope: !25, file: !1, line: 195, type: !14)
!109 = !DILocation(line: 195, column: 6, scope: !25)
!110 = !DILocalVariable(name: "fd", scope: !25, file: !1, line: 195, type: !14)
!111 = !DILocation(line: 195, column: 12, scope: !25)
!112 = !DILocalVariable(name: "i", scope: !25, file: !1, line: 195, type: !14)
!113 = !DILocation(line: 195, column: 16, scope: !25)
!114 = !DILocalVariable(name: "rdat", scope: !25, file: !1, line: 200, type: !115)
!115 = !DICompositeType(tag: DW_TAG_structure_type, scope: !25, file: !1, line: 196, size: 1216, align: 64, elements: !116)
!116 = !{!117, !126, !127}
!117 = !DIDerivedType(tag: DW_TAG_member, name: "tv", scope: !115, file: !1, line: 197, baseType: !118, size: 128, align: 64)
!118 = !DICompositeType(tag: DW_TAG_structure_type, name: "timeval", file: !119, line: 30, size: 128, align: 64, elements: !120)
!119 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!120 = !{!121, !124}
!121 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !118, file: !119, line: 32, baseType: !122, size: 64, align: 64)
!122 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !8, line: 139, baseType: !123)
!123 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !118, file: !119, line: 33, baseType: !125, size: 64, align: 64, offset: 64)
!125 = !DIDerivedType(tag: DW_TAG_typedef, name: "__suseconds_t", file: !8, line: 141, baseType: !123)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "pid", scope: !115, file: !1, line: 198, baseType: !38, size: 32, align: 32, offset: 128)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "rnd", scope: !115, file: !1, line: 199, baseType: !128, size: 1024, align: 8, offset: 160)
!128 = !DICompositeType(tag: DW_TAG_array_type, baseType: !5, size: 1024, align: 8, elements: !129)
!129 = !{!130}
!130 = !DISubrange(count: 128)
!131 = !DILocation(line: 200, column: 4, scope: !25)
!132 = !DILocation(line: 202, column: 7, scope: !133)
!133 = distinct !DILexicalBlock(scope: !25, file: !1, line: 202, column: 6)
!134 = !DILocation(line: 202, column: 6, scope: !25)
!135 = !DILocation(line: 203, column: 3, scope: !136)
!136 = distinct !DILexicalBlock(scope: !133, file: !1, line: 202, column: 23)
!137 = !DILocation(line: 204, column: 18, scope: !136)
!138 = !DILocation(line: 205, column: 2, scope: !136)
!139 = !DILocation(line: 206, column: 7, scope: !25)
!140 = !DILocation(line: 207, column: 7, scope: !25)
!141 = !DILocation(line: 207, column: 5, scope: !25)
!142 = !DILocation(line: 208, column: 6, scope: !143)
!143 = distinct !DILexicalBlock(scope: !25, file: !1, line: 208, column: 6)
!144 = !DILocation(line: 208, column: 9, scope: !143)
!145 = !DILocation(line: 208, column: 6, scope: !25)
!146 = !DILocation(line: 209, column: 12, scope: !147)
!147 = distinct !DILexicalBlock(scope: !148, file: !1, line: 209, column: 7)
!148 = distinct !DILexicalBlock(scope: !143, file: !1, line: 208, column: 15)
!149 = !DILocation(line: 209, column: 16, scope: !147)
!150 = !DILocation(line: 209, column: 7, scope: !147)
!151 = !DILocation(line: 209, column: 32, scope: !147)
!152 = !DILocation(line: 209, column: 7, scope: !148)
!153 = !DILocation(line: 210, column: 9, scope: !147)
!154 = !DILocation(line: 210, column: 4, scope: !147)
!155 = !DILocation(line: 211, column: 15, scope: !148)
!156 = !DILocation(line: 211, column: 9, scope: !148)
!157 = !DILocation(line: 212, column: 2, scope: !148)
!158 = !DILocation(line: 213, column: 7, scope: !159)
!159 = distinct !DILexicalBlock(scope: !25, file: !1, line: 213, column: 6)
!160 = !DILocation(line: 213, column: 6, scope: !25)
!161 = !DILocation(line: 214, column: 28, scope: !162)
!162 = distinct !DILexicalBlock(scope: !159, file: !1, line: 213, column: 13)
!163 = !DILocation(line: 214, column: 9, scope: !162)
!164 = !DILocation(line: 215, column: 14, scope: !162)
!165 = !DILocation(line: 215, column: 8, scope: !162)
!166 = !DILocation(line: 215, column: 12, scope: !162)
!167 = !DILocation(line: 217, column: 2, scope: !162)
!168 = !DILocation(line: 219, column: 17, scope: !25)
!169 = !DILocation(line: 219, column: 2, scope: !25)
!170 = !DILocation(line: 225, column: 9, scope: !171)
!171 = distinct !DILexicalBlock(scope: !25, file: !1, line: 225, column: 2)
!172 = !DILocation(line: 225, column: 7, scope: !171)
!173 = !DILocation(line: 225, column: 14, scope: !174)
!174 = !DILexicalBlockFile(scope: !175, file: !1, discriminator: 1)
!175 = distinct !DILexicalBlock(scope: !171, file: !1, line: 225, column: 2)
!176 = !DILocation(line: 225, column: 16, scope: !174)
!177 = !DILocation(line: 225, column: 2, scope: !174)
!178 = !DILocation(line: 226, column: 9, scope: !175)
!179 = !DILocation(line: 226, column: 3, scope: !175)
!180 = !DILocation(line: 225, column: 25, scope: !181)
!181 = !DILexicalBlockFile(scope: !175, file: !1, discriminator: 2)
!182 = !DILocation(line: 225, column: 2, scope: !181)
!183 = !DILocation(line: 227, column: 13, scope: !25)
!184 = !DILocation(line: 228, column: 1, scope: !25)
!185 = !DILocalVariable(name: "si", scope: !30, file: !1, line: 244, type: !33)
!186 = !DILocation(line: 244, column: 10, scope: !30)
!187 = !DILocalVariable(name: "sj", scope: !30, file: !1, line: 244, type: !33)
!188 = !DILocation(line: 244, column: 14, scope: !30)
!189 = !DILocation(line: 246, column: 13, scope: !30)
!190 = !DILocation(line: 246, column: 10, scope: !30)
!191 = !DILocation(line: 246, column: 15, scope: !30)
!192 = !DILocation(line: 246, column: 9, scope: !30)
!193 = !DILocation(line: 246, column: 7, scope: !30)
!194 = !DILocation(line: 247, column: 15, scope: !30)
!195 = !DILocation(line: 247, column: 7, scope: !30)
!196 = !DILocation(line: 247, column: 5, scope: !30)
!197 = !DILocation(line: 248, column: 13, scope: !30)
!198 = !DILocation(line: 248, column: 10, scope: !30)
!199 = !DILocation(line: 248, column: 17, scope: !30)
!200 = !DILocation(line: 248, column: 15, scope: !30)
!201 = !DILocation(line: 248, column: 9, scope: !30)
!202 = !DILocation(line: 248, column: 7, scope: !30)
!203 = !DILocation(line: 249, column: 15, scope: !30)
!204 = !DILocation(line: 249, column: 7, scope: !30)
!205 = !DILocation(line: 249, column: 5, scope: !30)
!206 = !DILocation(line: 250, column: 15, scope: !30)
!207 = !DILocation(line: 250, column: 10, scope: !30)
!208 = !DILocation(line: 250, column: 2, scope: !30)
!209 = !DILocation(line: 250, column: 13, scope: !30)
!210 = !DILocation(line: 251, column: 15, scope: !30)
!211 = !DILocation(line: 251, column: 10, scope: !30)
!212 = !DILocation(line: 251, column: 2, scope: !30)
!213 = !DILocation(line: 251, column: 13, scope: !30)
!214 = !DILocation(line: 252, column: 16, scope: !30)
!215 = !DILocation(line: 252, column: 21, scope: !30)
!216 = !DILocation(line: 252, column: 19, scope: !30)
!217 = !DILocation(line: 252, column: 25, scope: !30)
!218 = !DILocation(line: 252, column: 10, scope: !30)
!219 = !DILocation(line: 252, column: 2, scope: !30)
!220 = !DILocalVariable(name: "n", scope: !26, file: !1, line: 167, type: !14)
!221 = !DILocation(line: 167, column: 10, scope: !26)
!222 = !DILocation(line: 169, column: 9, scope: !223)
!223 = distinct !DILexicalBlock(scope: !26, file: !1, line: 169, column: 2)
!224 = !DILocation(line: 169, column: 7, scope: !223)
!225 = !DILocation(line: 169, column: 14, scope: !226)
!226 = !DILexicalBlockFile(scope: !227, file: !1, discriminator: 1)
!227 = distinct !DILexicalBlock(scope: !223, file: !1, line: 169, column: 2)
!228 = !DILocation(line: 169, column: 16, scope: !226)
!229 = !DILocation(line: 169, column: 2, scope: !226)
!230 = !DILocation(line: 170, column: 13, scope: !227)
!231 = !DILocation(line: 170, column: 8, scope: !227)
!232 = !DILocation(line: 170, column: 3, scope: !227)
!233 = !DILocation(line: 170, column: 11, scope: !227)
!234 = !DILocation(line: 169, column: 24, scope: !235)
!235 = !DILexicalBlockFile(scope: !227, file: !1, discriminator: 2)
!236 = !DILocation(line: 169, column: 2, scope: !235)
!237 = !DILocation(line: 171, column: 7, scope: !26)
!238 = !DILocation(line: 172, column: 7, scope: !26)
!239 = !DILocation(line: 173, column: 1, scope: !26)
!240 = !DILocalVariable(name: "dat", arg: 1, scope: !27, file: !1, line: 176, type: !4)
!241 = !DILocation(line: 176, column: 24, scope: !27)
!242 = !DILocalVariable(name: "datlen", arg: 2, scope: !27, file: !1, line: 176, type: !14)
!243 = !DILocation(line: 176, column: 33, scope: !27)
!244 = !DILocalVariable(name: "n", scope: !27, file: !1, line: 178, type: !14)
!245 = !DILocation(line: 178, column: 10, scope: !27)
!246 = !DILocalVariable(name: "si", scope: !27, file: !1, line: 179, type: !33)
!247 = !DILocation(line: 179, column: 10, scope: !27)
!248 = !DILocation(line: 181, column: 6, scope: !27)
!249 = !DILocation(line: 182, column: 9, scope: !250)
!250 = distinct !DILexicalBlock(scope: !27, file: !1, line: 182, column: 2)
!251 = !DILocation(line: 182, column: 7, scope: !250)
!252 = !DILocation(line: 182, column: 14, scope: !253)
!253 = !DILexicalBlockFile(scope: !254, file: !1, discriminator: 1)
!254 = distinct !DILexicalBlock(scope: !250, file: !1, line: 182, column: 2)
!255 = !DILocation(line: 182, column: 16, scope: !253)
!256 = !DILocation(line: 182, column: 2, scope: !253)
!257 = !DILocation(line: 183, column: 14, scope: !258)
!258 = distinct !DILexicalBlock(scope: !254, file: !1, line: 182, column: 28)
!259 = !DILocation(line: 183, column: 11, scope: !258)
!260 = !DILocation(line: 183, column: 16, scope: !258)
!261 = !DILocation(line: 183, column: 10, scope: !258)
!262 = !DILocation(line: 183, column: 8, scope: !258)
!263 = !DILocation(line: 184, column: 16, scope: !258)
!264 = !DILocation(line: 184, column: 8, scope: !258)
!265 = !DILocation(line: 184, column: 6, scope: !258)
!266 = !DILocation(line: 185, column: 14, scope: !258)
!267 = !DILocation(line: 185, column: 11, scope: !258)
!268 = !DILocation(line: 185, column: 18, scope: !258)
!269 = !DILocation(line: 185, column: 16, scope: !258)
!270 = !DILocation(line: 185, column: 27, scope: !258)
!271 = !DILocation(line: 185, column: 31, scope: !258)
!272 = !DILocation(line: 185, column: 29, scope: !258)
!273 = !DILocation(line: 185, column: 23, scope: !258)
!274 = !DILocation(line: 185, column: 21, scope: !258)
!275 = !DILocation(line: 185, column: 10, scope: !258)
!276 = !DILocation(line: 185, column: 8, scope: !258)
!277 = !DILocation(line: 186, column: 24, scope: !258)
!278 = !DILocation(line: 186, column: 16, scope: !258)
!279 = !DILocation(line: 186, column: 11, scope: !258)
!280 = !DILocation(line: 186, column: 3, scope: !258)
!281 = !DILocation(line: 186, column: 14, scope: !258)
!282 = !DILocation(line: 187, column: 16, scope: !258)
!283 = !DILocation(line: 187, column: 11, scope: !258)
!284 = !DILocation(line: 187, column: 3, scope: !258)
!285 = !DILocation(line: 187, column: 14, scope: !258)
!286 = !DILocation(line: 188, column: 2, scope: !258)
!287 = !DILocation(line: 182, column: 24, scope: !288)
!288 = !DILexicalBlockFile(scope: !254, file: !1, discriminator: 2)
!289 = !DILocation(line: 182, column: 2, scope: !288)
!290 = !DILocation(line: 189, column: 12, scope: !27)
!291 = !DILocation(line: 189, column: 7, scope: !27)
!292 = !DILocation(line: 190, column: 1, scope: !27)
