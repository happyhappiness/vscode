; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_encoder_mf.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_mf_s = type { i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32 (%struct.lzma_mf_s*, %struct.lzma_match*)*, void (%struct.lzma_mf_s*, i32)*, i32*, i32*, i32, i32, i32, i32, i32, i32, i32, i32, i32 }
%struct.lzma_match = type { i32, i32 }

@.str = private unnamed_addr constant [31 x i8] c"matches[i].len <= mf->nice_len\00", align 1
@.str.1 = private unnamed_addr constant [81 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_encoder_mf.c\00", align 1
@__PRETTY_FUNCTION__.lzma_mf_find = private unnamed_addr constant [59 x i8] c"uint32_t lzma_mf_find(lzma_mf *, uint32_t *, lzma_match *)\00", align 1
@.str.2 = private unnamed_addr constant [31 x i8] c"matches[i].dist < mf->read_pos\00", align 1
@.str.3 = private unnamed_addr constant [78 x i8] c"memcmp(mf_ptr(mf) - 1, mf_ptr(mf) - matches[i].dist - 2, matches[i].len) == 0\00", align 1
@.str.4 = private unnamed_addr constant [23 x i8] c"mf->action != LZMA_RUN\00", align 1
@__PRETTY_FUNCTION__.lzma_mf_hc3_find = private unnamed_addr constant [51 x i8] c"uint32_t lzma_mf_hc3_find(lzma_mf *, lzma_match *)\00", align 1
@lzma_crc32_table = external constant [8 x [256 x i32]], align 16
@__PRETTY_FUNCTION__.lzma_mf_hc4_find = private unnamed_addr constant [51 x i8] c"uint32_t lzma_mf_hc4_find(lzma_mf *, lzma_match *)\00", align 1
@__PRETTY_FUNCTION__.lzma_mf_bt2_find = private unnamed_addr constant [51 x i8] c"uint32_t lzma_mf_bt2_find(lzma_mf *, lzma_match *)\00", align 1
@__PRETTY_FUNCTION__.lzma_mf_bt2_skip = private unnamed_addr constant [43 x i8] c"void lzma_mf_bt2_skip(lzma_mf *, uint32_t)\00", align 1
@__PRETTY_FUNCTION__.lzma_mf_bt3_find = private unnamed_addr constant [51 x i8] c"uint32_t lzma_mf_bt3_find(lzma_mf *, lzma_match *)\00", align 1
@__PRETTY_FUNCTION__.lzma_mf_bt3_skip = private unnamed_addr constant [43 x i8] c"void lzma_mf_bt3_skip(lzma_mf *, uint32_t)\00", align 1
@__PRETTY_FUNCTION__.lzma_mf_bt4_find = private unnamed_addr constant [51 x i8] c"uint32_t lzma_mf_bt4_find(lzma_mf *, lzma_match *)\00", align 1
@__PRETTY_FUNCTION__.lzma_mf_bt4_skip = private unnamed_addr constant [43 x i8] c"void lzma_mf_bt4_skip(lzma_mf *, uint32_t)\00", align 1
@.str.5 = private unnamed_addr constant [30 x i8] c"mf->read_pos <= mf->write_pos\00", align 1
@__PRETTY_FUNCTION__.move_pending = private unnamed_addr constant [29 x i8] c"void move_pending(lzma_mf *)\00", align 1
@__PRETTY_FUNCTION__.move_pos = private unnamed_addr constant [25 x i8] c"void move_pos(lzma_mf *)\00", align 1
@.str.6 = private unnamed_addr constant [43 x i8] c"mf->read_pos + mf->offset == (4294967295U)\00", align 1
@__PRETTY_FUNCTION__.normalize = private unnamed_addr constant [26 x i8] c"void normalize(lzma_mf *)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_mf_find(%struct.lzma_mf_s* %mf, i32* %count_ptr, %struct.lzma_match* %matches) #0 !dbg !19 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %count_ptr.addr = alloca i32*, align 8
  %matches.addr = alloca %struct.lzma_match*, align 8
  %count = alloca i32, align 4
  %len_best = alloca i32, align 4
  %i = alloca i32, align 4
  %p1 = alloca i8*, align 8
  %p2 = alloca i8*, align 8
  %limit = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !106, metadata !107), !dbg !108
  store i32* %count_ptr, i32** %count_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %count_ptr.addr, metadata !109, metadata !107), !dbg !110
  store %struct.lzma_match* %matches, %struct.lzma_match** %matches.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_match** %matches.addr, metadata !111, metadata !107), !dbg !112
  call void @llvm.dbg.declare(metadata i32* %count, metadata !113, metadata !107), !dbg !114
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !115
  %find = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 10, !dbg !116
  %1 = load i32 (%struct.lzma_mf_s*, %struct.lzma_match*)*, i32 (%struct.lzma_mf_s*, %struct.lzma_match*)** %find, align 8, !dbg !116
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !117
  %3 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !118
  %call = call i32 %1(%struct.lzma_mf_s* %2, %struct.lzma_match* %3), !dbg !115
  store i32 %call, i32* %count, align 4, !dbg !114
  call void @llvm.dbg.declare(metadata i32* %len_best, metadata !119, metadata !107), !dbg !120
  store i32 0, i32* %len_best, align 4, !dbg !120
  %4 = load i32, i32* %count, align 4, !dbg !121
  %cmp = icmp ugt i32 %4, 0, !dbg !123
  br i1 %cmp, label %if.then, label %if.end59, !dbg !124

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %i, metadata !125, metadata !107), !dbg !127
  store i32 0, i32* %i, align 4, !dbg !128
  br label %for.cond, !dbg !130

for.cond:                                         ; preds = %for.inc, %if.then
  %5 = load i32, i32* %i, align 4, !dbg !131
  %6 = load i32, i32* %count, align 4, !dbg !134
  %cmp1 = icmp ult i32 %5, %6, !dbg !135
  br i1 %cmp1, label %for.body, label %for.end, !dbg !136

for.body:                                         ; preds = %for.cond
  %7 = load i32, i32* %i, align 4, !dbg !137
  %idxprom = zext i32 %7 to i64, !dbg !137
  %8 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !137
  %arrayidx = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %8, i64 %idxprom, !dbg !137
  %len = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx, i32 0, i32 0, !dbg !137
  %9 = load i32, i32* %len, align 4, !dbg !137
  %10 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !137
  %nice_len = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %10, i32 0, i32 18, !dbg !137
  %11 = load i32, i32* %nice_len, align 8, !dbg !137
  %cmp2 = icmp ule i32 %9, %11, !dbg !137
  br i1 %cmp2, label %cond.true, label %cond.false, !dbg !137

cond.true:                                        ; preds = %for.body
  br label %cond.end, !dbg !139

cond.false:                                       ; preds = %for.body
  call void @__assert_fail(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.1, i32 0, i32 0), i32 38, i8* getelementptr inbounds ([59 x i8], [59 x i8]* @__PRETTY_FUNCTION__.lzma_mf_find, i32 0, i32 0)) #5, !dbg !141
  unreachable, !dbg !141
                                                  ; No predecessors!
  br label %cond.end, !dbg !143

cond.end:                                         ; preds = %12, %cond.true
  %13 = load i32, i32* %i, align 4, !dbg !145
  %idxprom3 = zext i32 %13 to i64, !dbg !145
  %14 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !145
  %arrayidx4 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %14, i64 %idxprom3, !dbg !145
  %dist = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx4, i32 0, i32 1, !dbg !145
  %15 = load i32, i32* %dist, align 4, !dbg !145
  %16 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !145
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %16, i32 0, i32 5, !dbg !145
  %17 = load i32, i32* %read_pos, align 8, !dbg !145
  %cmp5 = icmp ult i32 %15, %17, !dbg !145
  br i1 %cmp5, label %cond.true6, label %cond.false7, !dbg !145

cond.true6:                                       ; preds = %cond.end
  br label %cond.end8, !dbg !146

cond.false7:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.1, i32 0, i32 0), i32 39, i8* getelementptr inbounds ([59 x i8], [59 x i8]* @__PRETTY_FUNCTION__.lzma_mf_find, i32 0, i32 0)) #5, !dbg !147
  unreachable, !dbg !147
                                                  ; No predecessors!
  br label %cond.end8, !dbg !148

cond.end8:                                        ; preds = %18, %cond.true6
  %19 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !149
  %call9 = call i8* @mf_ptr(%struct.lzma_mf_s* %19), !dbg !149
  %add.ptr = getelementptr inbounds i8, i8* %call9, i64 -1, !dbg !149
  %20 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !149
  %call10 = call i8* @mf_ptr(%struct.lzma_mf_s* %20), !dbg !150
  %21 = load i32, i32* %i, align 4, !dbg !149
  %idxprom11 = zext i32 %21 to i64, !dbg !149
  %22 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !149
  %arrayidx12 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %22, i64 %idxprom11, !dbg !149
  %dist13 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx12, i32 0, i32 1, !dbg !149
  %23 = load i32, i32* %dist13, align 4, !dbg !149
  %idx.ext = zext i32 %23 to i64, !dbg !149
  %idx.neg = sub i64 0, %idx.ext, !dbg !149
  %add.ptr14 = getelementptr inbounds i8, i8* %call10, i64 %idx.neg, !dbg !149
  %add.ptr15 = getelementptr inbounds i8, i8* %add.ptr14, i64 -2, !dbg !149
  %24 = load i32, i32* %i, align 4, !dbg !149
  %idxprom16 = zext i32 %24 to i64, !dbg !149
  %25 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !149
  %arrayidx17 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %25, i64 %idxprom16, !dbg !149
  %len18 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx17, i32 0, i32 0, !dbg !149
  %26 = load i32, i32* %len18, align 4, !dbg !149
  %conv = zext i32 %26 to i64, !dbg !149
  %call19 = call i32 @memcmp(i8* %add.ptr, i8* %add.ptr15, i64 %conv) #6, !dbg !152
  %cmp20 = icmp eq i32 %call19, 0, !dbg !149
  br i1 %cmp20, label %cond.true22, label %cond.false23, !dbg !149

cond.true22:                                      ; preds = %cond.end8
  br label %cond.end24, !dbg !154

cond.false23:                                     ; preds = %cond.end8
  call void @__assert_fail(i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.1, i32 0, i32 0), i32 42, i8* getelementptr inbounds ([59 x i8], [59 x i8]* @__PRETTY_FUNCTION__.lzma_mf_find, i32 0, i32 0)) #5, !dbg !155
  unreachable, !dbg !155
                                                  ; No predecessors!
  br label %cond.end24, !dbg !156

cond.end24:                                       ; preds = %27, %cond.true22
  br label %for.inc, !dbg !157

for.inc:                                          ; preds = %cond.end24
  %28 = load i32, i32* %i, align 4, !dbg !158
  %inc = add i32 %28, 1, !dbg !158
  store i32 %inc, i32* %i, align 4, !dbg !158
  br label %for.cond, !dbg !160

for.end:                                          ; preds = %for.cond
  %29 = load i32, i32* %count, align 4, !dbg !161
  %sub = sub i32 %29, 1, !dbg !162
  %idxprom25 = zext i32 %sub to i64, !dbg !163
  %30 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !163
  %arrayidx26 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %30, i64 %idxprom25, !dbg !163
  %len27 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx26, i32 0, i32 0, !dbg !164
  %31 = load i32, i32* %len27, align 4, !dbg !164
  store i32 %31, i32* %len_best, align 4, !dbg !165
  %32 = load i32, i32* %len_best, align 4, !dbg !166
  %33 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !168
  %nice_len28 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %33, i32 0, i32 18, !dbg !169
  %34 = load i32, i32* %nice_len28, align 8, !dbg !169
  %cmp29 = icmp eq i32 %32, %34, !dbg !170
  br i1 %cmp29, label %if.then31, label %if.end58, !dbg !171

if.then31:                                        ; preds = %for.end
  call void @llvm.dbg.declare(metadata i8** %p1, metadata !172, metadata !107), !dbg !174
  call void @llvm.dbg.declare(metadata i8** %p2, metadata !175, metadata !107), !dbg !176
  call void @llvm.dbg.declare(metadata i32* %limit, metadata !177, metadata !107), !dbg !178
  %35 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !179
  %call32 = call i32 @mf_avail(%struct.lzma_mf_s* %35), !dbg !180
  %add = add i32 %call32, 1, !dbg !181
  store i32 %add, i32* %limit, align 4, !dbg !178
  %36 = load i32, i32* %limit, align 4, !dbg !182
  %37 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !184
  %match_len_max = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %37, i32 0, i32 19, !dbg !185
  %38 = load i32, i32* %match_len_max, align 4, !dbg !185
  %cmp33 = icmp ugt i32 %36, %38, !dbg !186
  br i1 %cmp33, label %if.then35, label %if.end, !dbg !187

if.then35:                                        ; preds = %if.then31
  %39 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !188
  %match_len_max36 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %39, i32 0, i32 19, !dbg !189
  %40 = load i32, i32* %match_len_max36, align 4, !dbg !189
  store i32 %40, i32* %limit, align 4, !dbg !190
  br label %if.end, !dbg !191

if.end:                                           ; preds = %if.then35, %if.then31
  %41 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !192
  %call37 = call i8* @mf_ptr(%struct.lzma_mf_s* %41), !dbg !193
  %add.ptr38 = getelementptr inbounds i8, i8* %call37, i64 -1, !dbg !194
  store i8* %add.ptr38, i8** %p1, align 8, !dbg !195
  %42 = load i8*, i8** %p1, align 8, !dbg !196
  %43 = load i32, i32* %count, align 4, !dbg !197
  %sub39 = sub i32 %43, 1, !dbg !198
  %idxprom40 = zext i32 %sub39 to i64, !dbg !199
  %44 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !199
  %arrayidx41 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %44, i64 %idxprom40, !dbg !199
  %dist42 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx41, i32 0, i32 1, !dbg !200
  %45 = load i32, i32* %dist42, align 4, !dbg !200
  %idx.ext43 = zext i32 %45 to i64, !dbg !201
  %idx.neg44 = sub i64 0, %idx.ext43, !dbg !201
  %add.ptr45 = getelementptr inbounds i8, i8* %42, i64 %idx.neg44, !dbg !201
  %add.ptr46 = getelementptr inbounds i8, i8* %add.ptr45, i64 -1, !dbg !202
  store i8* %add.ptr46, i8** %p2, align 8, !dbg !203
  br label %while.cond, !dbg !204

while.cond:                                       ; preds = %while.body, %if.end
  %46 = load i32, i32* %len_best, align 4, !dbg !205
  %47 = load i32, i32* %limit, align 4, !dbg !207
  %cmp47 = icmp ult i32 %46, %47, !dbg !208
  br i1 %cmp47, label %land.rhs, label %land.end, !dbg !209

land.rhs:                                         ; preds = %while.cond
  %48 = load i32, i32* %len_best, align 4, !dbg !210
  %idxprom49 = zext i32 %48 to i64, !dbg !211
  %49 = load i8*, i8** %p1, align 8, !dbg !211
  %arrayidx50 = getelementptr inbounds i8, i8* %49, i64 %idxprom49, !dbg !211
  %50 = load i8, i8* %arrayidx50, align 1, !dbg !211
  %conv51 = zext i8 %50 to i32, !dbg !211
  %51 = load i32, i32* %len_best, align 4, !dbg !212
  %idxprom52 = zext i32 %51 to i64, !dbg !213
  %52 = load i8*, i8** %p2, align 8, !dbg !213
  %arrayidx53 = getelementptr inbounds i8, i8* %52, i64 %idxprom52, !dbg !213
  %53 = load i8, i8* %arrayidx53, align 1, !dbg !213
  %conv54 = zext i8 %53 to i32, !dbg !213
  %cmp55 = icmp eq i32 %conv51, %conv54, !dbg !214
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %54 = phi i1 [ false, %while.cond ], [ %cmp55, %land.rhs ]
  br i1 %54, label %while.body, label %while.end, !dbg !215

while.body:                                       ; preds = %land.end
  %55 = load i32, i32* %len_best, align 4, !dbg !217
  %inc57 = add i32 %55, 1, !dbg !217
  store i32 %inc57, i32* %len_best, align 4, !dbg !217
  br label %while.cond, !dbg !218

while.end:                                        ; preds = %land.end
  br label %if.end58, !dbg !220

if.end58:                                         ; preds = %while.end, %for.end
  br label %if.end59, !dbg !221

if.end59:                                         ; preds = %if.end58, %entry
  %56 = load i32, i32* %count, align 4, !dbg !222
  %57 = load i32*, i32** %count_ptr.addr, align 8, !dbg !223
  store i32 %56, i32* %57, align 4, !dbg !224
  %58 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !225
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %58, i32 0, i32 6, !dbg !226
  %59 = load i32, i32* %read_ahead, align 4, !dbg !227
  %inc60 = add i32 %59, 1, !dbg !227
  store i32 %inc60, i32* %read_ahead, align 4, !dbg !227
  %60 = load i32, i32* %len_best, align 4, !dbg !228
  ret i32 %60, !dbg !229
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #2

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #3

; Function Attrs: inlinehint nounwind uwtable
define internal i8* @mf_ptr(%struct.lzma_mf_s* %mf) #4 !dbg !78 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !230, metadata !107), !dbg !231
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !232
  %buffer = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 0, !dbg !233
  %1 = load i8*, i8** %buffer, align 8, !dbg !233
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !234
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 5, !dbg !235
  %3 = load i32, i32* %read_pos, align 8, !dbg !235
  %idx.ext = zext i32 %3 to i64, !dbg !236
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 %idx.ext, !dbg !236
  ret i8* %add.ptr, !dbg !237
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @mf_avail(%struct.lzma_mf_s* %mf) #4 !dbg !83 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !238, metadata !107), !dbg !239
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !240
  %write_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 8, !dbg !241
  %1 = load i32, i32* %write_pos, align 4, !dbg !241
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !242
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 5, !dbg !243
  %3 = load i32, i32* %read_pos, align 8, !dbg !243
  %sub = sub i32 %1, %3, !dbg !244
  ret i32 %sub, !dbg !245
}

; Function Attrs: nounwind uwtable
define i32 @lzma_mf_hc3_find(%struct.lzma_mf_s* %mf, %struct.lzma_match* %matches) #0 !dbg !68 {
entry:
  %retval = alloca i32, align 4
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %matches.addr = alloca %struct.lzma_match*, align 8
  %cur = alloca i8*, align 8
  %pos = alloca i32, align 4
  %temp = alloca i32, align 4
  %hash_value = alloca i32, align 4
  %hash_2_value = alloca i32, align 4
  %delta2 = alloca i32, align 4
  %cur_match = alloca i32, align 4
  %len_best = alloca i32, align 4
  %matches_count = alloca i32, align 4
  %len_limit = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !246, metadata !107), !dbg !247
  store %struct.lzma_match* %matches, %struct.lzma_match** %matches.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_match** %matches.addr, metadata !248, metadata !107), !dbg !249
  call void @llvm.dbg.declare(metadata i8** %cur, metadata !250, metadata !107), !dbg !251
  call void @llvm.dbg.declare(metadata i32* %pos, metadata !252, metadata !107), !dbg !253
  call void @llvm.dbg.declare(metadata i32* %temp, metadata !254, metadata !107), !dbg !255
  call void @llvm.dbg.declare(metadata i32* %hash_value, metadata !256, metadata !107), !dbg !257
  call void @llvm.dbg.declare(metadata i32* %hash_2_value, metadata !258, metadata !107), !dbg !259
  call void @llvm.dbg.declare(metadata i32* %delta2, metadata !260, metadata !107), !dbg !261
  call void @llvm.dbg.declare(metadata i32* %cur_match, metadata !262, metadata !107), !dbg !263
  call void @llvm.dbg.declare(metadata i32* %len_best, metadata !264, metadata !107), !dbg !265
  store i32 2, i32* %len_best, align 4, !dbg !265
  call void @llvm.dbg.declare(metadata i32* %matches_count, metadata !266, metadata !107), !dbg !267
  store i32 0, i32* %matches_count, align 4, !dbg !267
  call void @llvm.dbg.declare(metadata i32* %len_limit, metadata !268, metadata !107), !dbg !269
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !269
  %call = call i32 @mf_avail(%struct.lzma_mf_s* %0), !dbg !269
  store i32 %call, i32* %len_limit, align 4, !dbg !269
  %1 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !270
  %nice_len = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %1, i32 0, i32 18, !dbg !270
  %2 = load i32, i32* %nice_len, align 8, !dbg !270
  %3 = load i32, i32* %len_limit, align 4, !dbg !270
  %cmp = icmp ule i32 %2, %3, !dbg !270
  br i1 %cmp, label %if.then, label %if.else, !dbg !269

if.then:                                          ; preds = %entry
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !272
  %nice_len1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %4, i32 0, i32 18, !dbg !272
  %5 = load i32, i32* %nice_len1, align 8, !dbg !272
  store i32 %5, i32* %len_limit, align 4, !dbg !272
  br label %if.end5, !dbg !272

if.else:                                          ; preds = %entry
  %6 = load i32, i32* %len_limit, align 4, !dbg !275
  %cmp2 = icmp ult i32 %6, 3, !dbg !275
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !275

if.then3:                                         ; preds = %if.else
  %7 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !278
  %action = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %7, i32 0, i32 20, !dbg !278
  %8 = load i32, i32* %action, align 8, !dbg !278
  %cmp4 = icmp ne i32 %8, 0, !dbg !278
  br i1 %cmp4, label %cond.true, label %cond.false, !dbg !278

cond.true:                                        ; preds = %if.then3
  br label %cond.end, !dbg !281

cond.false:                                       ; preds = %if.then3
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.1, i32 0, i32 0), i32 323, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @__PRETTY_FUNCTION__.lzma_mf_hc3_find, i32 0, i32 0)) #5, !dbg !283
  unreachable, !dbg !283
                                                  ; No predecessors!
  br label %cond.end, !dbg !285

cond.end:                                         ; preds = %9, %cond.true
  %10 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !287
  call void @move_pending(%struct.lzma_mf_s* %10), !dbg !287
  store i32 0, i32* %retval, align 4, !dbg !287
  br label %do.end66, !dbg !287

if.end:                                           ; preds = %if.else
  br label %if.end5

if.end5:                                          ; preds = %if.end, %if.then
  %11 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !289
  %call6 = call i8* @mf_ptr(%struct.lzma_mf_s* %11), !dbg !289
  store i8* %call6, i8** %cur, align 8, !dbg !289
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !289
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %12, i32 0, i32 5, !dbg !289
  %13 = load i32, i32* %read_pos, align 8, !dbg !289
  %14 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !289
  %offset = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %14, i32 0, i32 4, !dbg !289
  %15 = load i32, i32* %offset, align 4, !dbg !289
  %add = add i32 %13, %15, !dbg !289
  store i32 %add, i32* %pos, align 4, !dbg !289
  %16 = load i8*, i8** %cur, align 8, !dbg !291
  %arrayidx = getelementptr inbounds i8, i8* %16, i64 0, !dbg !291
  %17 = load i8, i8* %arrayidx, align 1, !dbg !291
  %idxprom = zext i8 %17 to i64, !dbg !291
  %arrayidx7 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom, !dbg !291
  %18 = load i32, i32* %arrayidx7, align 4, !dbg !291
  %19 = load i8*, i8** %cur, align 8, !dbg !291
  %arrayidx8 = getelementptr inbounds i8, i8* %19, i64 1, !dbg !291
  %20 = load i8, i8* %arrayidx8, align 1, !dbg !291
  %conv = zext i8 %20 to i32, !dbg !291
  %xor = xor i32 %18, %conv, !dbg !291
  store i32 %xor, i32* %temp, align 4, !dbg !291
  %21 = load i32, i32* %temp, align 4, !dbg !291
  %and = and i32 %21, 1023, !dbg !291
  store i32 %and, i32* %hash_2_value, align 4, !dbg !291
  %22 = load i32, i32* %temp, align 4, !dbg !291
  %23 = load i8*, i8** %cur, align 8, !dbg !291
  %arrayidx9 = getelementptr inbounds i8, i8* %23, i64 2, !dbg !291
  %24 = load i8, i8* %arrayidx9, align 1, !dbg !291
  %conv10 = zext i8 %24 to i32, !dbg !291
  %shl = shl i32 %conv10, 8, !dbg !291
  %xor11 = xor i32 %22, %shl, !dbg !291
  %25 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !291
  %hash_mask = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %25, i32 0, i32 16, !dbg !291
  %26 = load i32, i32* %hash_mask, align 8, !dbg !291
  %and12 = and i32 %xor11, %26, !dbg !291
  store i32 %and12, i32* %hash_value, align 4, !dbg !291
  %27 = load i32, i32* %pos, align 4, !dbg !292
  %28 = load i32, i32* %hash_2_value, align 4, !dbg !293
  %idxprom13 = zext i32 %28 to i64, !dbg !294
  %29 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !294
  %hash = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %29, i32 0, i32 12, !dbg !295
  %30 = load i32*, i32** %hash, align 8, !dbg !295
  %arrayidx14 = getelementptr inbounds i32, i32* %30, i64 %idxprom13, !dbg !294
  %31 = load i32, i32* %arrayidx14, align 4, !dbg !294
  %sub = sub i32 %27, %31, !dbg !296
  store i32 %sub, i32* %delta2, align 4, !dbg !297
  %32 = load i32, i32* %hash_value, align 4, !dbg !298
  %add15 = add i32 1024, %32, !dbg !299
  %idxprom16 = zext i32 %add15 to i64, !dbg !300
  %33 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !300
  %hash17 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %33, i32 0, i32 12, !dbg !301
  %34 = load i32*, i32** %hash17, align 8, !dbg !301
  %arrayidx18 = getelementptr inbounds i32, i32* %34, i64 %idxprom16, !dbg !300
  %35 = load i32, i32* %arrayidx18, align 4, !dbg !300
  store i32 %35, i32* %cur_match, align 4, !dbg !302
  %36 = load i32, i32* %pos, align 4, !dbg !303
  %37 = load i32, i32* %hash_2_value, align 4, !dbg !304
  %idxprom19 = zext i32 %37 to i64, !dbg !305
  %38 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !305
  %hash20 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %38, i32 0, i32 12, !dbg !306
  %39 = load i32*, i32** %hash20, align 8, !dbg !306
  %arrayidx21 = getelementptr inbounds i32, i32* %39, i64 %idxprom19, !dbg !305
  store i32 %36, i32* %arrayidx21, align 4, !dbg !307
  %40 = load i32, i32* %pos, align 4, !dbg !308
  %41 = load i32, i32* %hash_value, align 4, !dbg !309
  %add22 = add i32 1024, %41, !dbg !310
  %idxprom23 = zext i32 %add22 to i64, !dbg !311
  %42 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !311
  %hash24 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %42, i32 0, i32 12, !dbg !312
  %43 = load i32*, i32** %hash24, align 8, !dbg !312
  %arrayidx25 = getelementptr inbounds i32, i32* %43, i64 %idxprom23, !dbg !311
  store i32 %40, i32* %arrayidx25, align 4, !dbg !313
  %44 = load i32, i32* %delta2, align 4, !dbg !314
  %45 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !316
  %cyclic_size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %45, i32 0, i32 15, !dbg !317
  %46 = load i32, i32* %cyclic_size, align 4, !dbg !317
  %cmp26 = icmp ult i32 %44, %46, !dbg !318
  br i1 %cmp26, label %land.lhs.true, label %if.end57, !dbg !319

land.lhs.true:                                    ; preds = %if.end5
  %47 = load i8*, i8** %cur, align 8, !dbg !320
  %48 = load i32, i32* %delta2, align 4, !dbg !322
  %idx.ext = zext i32 %48 to i64, !dbg !323
  %idx.neg = sub i64 0, %idx.ext, !dbg !323
  %add.ptr = getelementptr inbounds i8, i8* %47, i64 %idx.neg, !dbg !323
  %49 = load i8, i8* %add.ptr, align 1, !dbg !324
  %conv28 = zext i8 %49 to i32, !dbg !324
  %50 = load i8*, i8** %cur, align 8, !dbg !325
  %51 = load i8, i8* %50, align 1, !dbg !326
  %conv29 = zext i8 %51 to i32, !dbg !326
  %cmp30 = icmp eq i32 %conv28, %conv29, !dbg !327
  br i1 %cmp30, label %if.then32, label %if.end57, !dbg !328

if.then32:                                        ; preds = %land.lhs.true
  br label %for.cond, !dbg !329

for.cond:                                         ; preds = %for.inc, %if.then32
  %52 = load i32, i32* %len_best, align 4, !dbg !331
  %53 = load i32, i32* %len_limit, align 4, !dbg !335
  %cmp33 = icmp ne i32 %52, %53, !dbg !336
  br i1 %cmp33, label %for.body, label %for.end, !dbg !337

for.body:                                         ; preds = %for.cond
  %54 = load i8*, i8** %cur, align 8, !dbg !338
  %55 = load i32, i32* %len_best, align 4, !dbg !340
  %idx.ext35 = zext i32 %55 to i64, !dbg !341
  %add.ptr36 = getelementptr inbounds i8, i8* %54, i64 %idx.ext35, !dbg !341
  %56 = load i32, i32* %delta2, align 4, !dbg !342
  %idx.ext37 = zext i32 %56 to i64, !dbg !343
  %idx.neg38 = sub i64 0, %idx.ext37, !dbg !343
  %add.ptr39 = getelementptr inbounds i8, i8* %add.ptr36, i64 %idx.neg38, !dbg !343
  %57 = load i8, i8* %add.ptr39, align 1, !dbg !344
  %conv40 = zext i8 %57 to i32, !dbg !344
  %58 = load i32, i32* %len_best, align 4, !dbg !345
  %idxprom41 = zext i32 %58 to i64, !dbg !346
  %59 = load i8*, i8** %cur, align 8, !dbg !346
  %arrayidx42 = getelementptr inbounds i8, i8* %59, i64 %idxprom41, !dbg !346
  %60 = load i8, i8* %arrayidx42, align 1, !dbg !346
  %conv43 = zext i8 %60 to i32, !dbg !346
  %cmp44 = icmp ne i32 %conv40, %conv43, !dbg !347
  br i1 %cmp44, label %if.then46, label %if.end47, !dbg !348

if.then46:                                        ; preds = %for.body
  br label %for.end, !dbg !349

if.end47:                                         ; preds = %for.body
  br label %for.inc, !dbg !350

for.inc:                                          ; preds = %if.end47
  %61 = load i32, i32* %len_best, align 4, !dbg !352
  %inc = add i32 %61, 1, !dbg !352
  store i32 %inc, i32* %len_best, align 4, !dbg !352
  br label %for.cond, !dbg !354

for.end:                                          ; preds = %if.then46, %for.cond
  %62 = load i32, i32* %len_best, align 4, !dbg !355
  %63 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !356
  %arrayidx48 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %63, i64 0, !dbg !356
  %len = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx48, i32 0, i32 0, !dbg !357
  store i32 %62, i32* %len, align 4, !dbg !358
  %64 = load i32, i32* %delta2, align 4, !dbg !359
  %sub49 = sub i32 %64, 1, !dbg !360
  %65 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !361
  %arrayidx50 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %65, i64 0, !dbg !361
  %dist = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx50, i32 0, i32 1, !dbg !362
  store i32 %sub49, i32* %dist, align 4, !dbg !363
  store i32 1, i32* %matches_count, align 4, !dbg !364
  %66 = load i32, i32* %len_best, align 4, !dbg !365
  %67 = load i32, i32* %len_limit, align 4, !dbg !367
  %cmp51 = icmp eq i32 %66, %67, !dbg !368
  br i1 %cmp51, label %if.then53, label %if.end56, !dbg !369

if.then53:                                        ; preds = %for.end
  br label %do.body, !dbg !370

do.body:                                          ; preds = %if.then53
  %68 = load i32, i32* %cur_match, align 4, !dbg !372
  %69 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !372
  %cyclic_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %69, i32 0, i32 14, !dbg !372
  %70 = load i32, i32* %cyclic_pos, align 8, !dbg !372
  %idxprom54 = zext i32 %70 to i64, !dbg !372
  %71 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !372
  %son = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %71, i32 0, i32 13, !dbg !372
  %72 = load i32*, i32** %son, align 8, !dbg !372
  %arrayidx55 = getelementptr inbounds i32, i32* %72, i64 %idxprom54, !dbg !372
  store i32 %68, i32* %arrayidx55, align 4, !dbg !372
  %73 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !372
  call void @move_pos(%struct.lzma_mf_s* %73), !dbg !372
  br label %do.end, !dbg !372

do.end:                                           ; preds = %do.body
  store i32 1, i32* %retval, align 4, !dbg !375
  br label %do.end66, !dbg !375

if.end56:                                         ; preds = %for.end
  br label %if.end57, !dbg !376

if.end57:                                         ; preds = %if.end56, %land.lhs.true, %if.end5
  br label %do.body58, !dbg !377

do.body58:                                        ; preds = %if.end57
  %74 = load i32, i32* %len_limit, align 4, !dbg !378
  %75 = load i32, i32* %pos, align 4, !dbg !378
  %76 = load i8*, i8** %cur, align 8, !dbg !378
  %77 = load i32, i32* %cur_match, align 4, !dbg !378
  %78 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !378
  %depth = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %78, i32 0, i32 17, !dbg !378
  %79 = load i32, i32* %depth, align 4, !dbg !378
  %80 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !378
  %son59 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %80, i32 0, i32 13, !dbg !378
  %81 = load i32*, i32** %son59, align 8, !dbg !378
  %82 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !378
  %cyclic_pos60 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %82, i32 0, i32 14, !dbg !378
  %83 = load i32, i32* %cyclic_pos60, align 8, !dbg !378
  %84 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !378
  %cyclic_size61 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %84, i32 0, i32 15, !dbg !378
  %85 = load i32, i32* %cyclic_size61, align 4, !dbg !378
  %86 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !378
  %87 = load i32, i32* %matches_count, align 4, !dbg !378
  %idx.ext62 = zext i32 %87 to i64, !dbg !378
  %add.ptr63 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %86, i64 %idx.ext62, !dbg !378
  %88 = load i32, i32* %len_best, align 4, !dbg !378
  %call64 = call %struct.lzma_match* @hc_find_func(i32 %74, i32 %75, i8* %76, i32 %77, i32 %79, i32* %81, i32 %83, i32 %85, %struct.lzma_match* %add.ptr63, i32 %88), !dbg !378
  %89 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !378
  %sub.ptr.lhs.cast = ptrtoint %struct.lzma_match* %call64 to i64, !dbg !378
  %sub.ptr.rhs.cast = ptrtoint %struct.lzma_match* %89 to i64, !dbg !378
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !378
  %sub.ptr.div = sdiv exact i64 %sub.ptr.sub, 8, !dbg !378
  %conv65 = trunc i64 %sub.ptr.div to i32, !dbg !378
  store i32 %conv65, i32* %matches_count, align 4, !dbg !378
  %90 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !378
  call void @move_pos(%struct.lzma_mf_s* %90), !dbg !381
  %91 = load i32, i32* %matches_count, align 4, !dbg !378
  store i32 %91, i32* %retval, align 4, !dbg !378
  br label %do.end66, !dbg !378

do.end66:                                         ; preds = %cond.end, %do.end, %do.body58
  %92 = load i32, i32* %retval, align 4, !dbg !383
  ret i32 %92, !dbg !383
}

; Function Attrs: nounwind uwtable
define internal void @move_pending(%struct.lzma_mf_s* %mf) #0 !dbg !86 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !384, metadata !107), !dbg !385
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !386
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 5, !dbg !387
  %1 = load i32, i32* %read_pos, align 8, !dbg !388
  %inc = add i32 %1, 1, !dbg !388
  store i32 %inc, i32* %read_pos, align 8, !dbg !388
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !389
  %read_pos1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 5, !dbg !389
  %3 = load i32, i32* %read_pos1, align 8, !dbg !389
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !389
  %write_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %4, i32 0, i32 8, !dbg !389
  %5 = load i32, i32* %write_pos, align 4, !dbg !389
  %cmp = icmp ule i32 %3, %5, !dbg !389
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !389

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !390

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.1, i32 0, i32 0), i32 187, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @__PRETTY_FUNCTION__.move_pending, i32 0, i32 0)) #5, !dbg !392
  unreachable, !dbg !392
                                                  ; No predecessors!
  br label %cond.end, !dbg !394

cond.end:                                         ; preds = %6, %cond.true
  %7 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !396
  %pending = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %7, i32 0, i32 9, !dbg !397
  %8 = load i32, i32* %pending, align 8, !dbg !398
  %inc2 = add i32 %8, 1, !dbg !398
  store i32 %inc2, i32* %pending, align 8, !dbg !398
  ret void, !dbg !399
}

; Function Attrs: nounwind uwtable
define internal void @move_pos(%struct.lzma_mf_s* %mf) #0 !dbg !89 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !400, metadata !107), !dbg !401
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !402
  %cyclic_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 14, !dbg !404
  %1 = load i32, i32* %cyclic_pos, align 8, !dbg !405
  %inc = add i32 %1, 1, !dbg !405
  store i32 %inc, i32* %cyclic_pos, align 8, !dbg !405
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !406
  %cyclic_size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 15, !dbg !407
  %3 = load i32, i32* %cyclic_size, align 4, !dbg !407
  %cmp = icmp eq i32 %inc, %3, !dbg !408
  br i1 %cmp, label %if.then, label %if.end, !dbg !409

if.then:                                          ; preds = %entry
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !410
  %cyclic_pos1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %4, i32 0, i32 14, !dbg !411
  store i32 0, i32* %cyclic_pos1, align 8, !dbg !412
  br label %if.end, !dbg !410

if.end:                                           ; preds = %if.then, %entry
  %5 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !413
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %5, i32 0, i32 5, !dbg !414
  %6 = load i32, i32* %read_pos, align 8, !dbg !415
  %inc2 = add i32 %6, 1, !dbg !415
  store i32 %inc2, i32* %read_pos, align 8, !dbg !415
  %7 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !416
  %read_pos3 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %7, i32 0, i32 5, !dbg !416
  %8 = load i32, i32* %read_pos3, align 8, !dbg !416
  %9 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !416
  %write_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %9, i32 0, i32 8, !dbg !416
  %10 = load i32, i32* %write_pos, align 4, !dbg !416
  %cmp4 = icmp ule i32 %8, %10, !dbg !416
  br i1 %cmp4, label %cond.true, label %cond.false, !dbg !416

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !417

cond.false:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.1, i32 0, i32 0), i32 162, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @__PRETTY_FUNCTION__.move_pos, i32 0, i32 0)) #5, !dbg !419
  unreachable, !dbg !419
                                                  ; No predecessors!
  br label %cond.end, !dbg !421

cond.end:                                         ; preds = %11, %cond.true
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !423
  %read_pos5 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %12, i32 0, i32 5, !dbg !423
  %13 = load i32, i32* %read_pos5, align 8, !dbg !423
  %14 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !423
  %offset = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %14, i32 0, i32 4, !dbg !423
  %15 = load i32, i32* %offset, align 4, !dbg !423
  %add = add i32 %13, %15, !dbg !423
  %cmp6 = icmp eq i32 %add, -1, !dbg !423
  %conv = zext i1 %cmp6 to i32, !dbg !423
  %conv7 = sext i32 %conv to i64, !dbg !423
  %tobool = icmp ne i64 %conv7, 0, !dbg !423
  br i1 %tobool, label %if.then8, label %if.end9, !dbg !425

if.then8:                                         ; preds = %cond.end
  %16 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !426
  call void @normalize(%struct.lzma_mf_s* %16), !dbg !427
  br label %if.end9, !dbg !427

if.end9:                                          ; preds = %if.then8, %cond.end
  ret void, !dbg !428
}

; Function Attrs: nounwind uwtable
define internal %struct.lzma_match* @hc_find_func(i32 %len_limit, i32 %pos, i8* %cur, i32 %cur_match, i32 %depth, i32* %son, i32 %cyclic_pos, i32 %cyclic_size, %struct.lzma_match* %matches, i32 %len_best) #0 !dbg !91 {
entry:
  %retval = alloca %struct.lzma_match*, align 8
  %len_limit.addr = alloca i32, align 4
  %pos.addr = alloca i32, align 4
  %cur.addr = alloca i8*, align 8
  %cur_match.addr = alloca i32, align 4
  %depth.addr = alloca i32, align 4
  %son.addr = alloca i32*, align 8
  %cyclic_pos.addr = alloca i32, align 4
  %cyclic_size.addr = alloca i32, align 4
  %matches.addr = alloca %struct.lzma_match*, align 8
  %len_best.addr = alloca i32, align 4
  %delta = alloca i32, align 4
  %pb = alloca i8*, align 8
  %len = alloca i32, align 4
  store i32 %len_limit, i32* %len_limit.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len_limit.addr, metadata !429, metadata !107), !dbg !430
  store i32 %pos, i32* %pos.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos.addr, metadata !431, metadata !107), !dbg !432
  store i8* %cur, i8** %cur.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cur.addr, metadata !433, metadata !107), !dbg !434
  store i32 %cur_match, i32* %cur_match.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %cur_match.addr, metadata !435, metadata !107), !dbg !436
  store i32 %depth, i32* %depth.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %depth.addr, metadata !437, metadata !107), !dbg !438
  store i32* %son, i32** %son.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %son.addr, metadata !439, metadata !107), !dbg !440
  store i32 %cyclic_pos, i32* %cyclic_pos.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %cyclic_pos.addr, metadata !441, metadata !107), !dbg !442
  store i32 %cyclic_size, i32* %cyclic_size.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %cyclic_size.addr, metadata !443, metadata !107), !dbg !444
  store %struct.lzma_match* %matches, %struct.lzma_match** %matches.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_match** %matches.addr, metadata !445, metadata !107), !dbg !446
  store i32 %len_best, i32* %len_best.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len_best.addr, metadata !447, metadata !107), !dbg !448
  %0 = load i32, i32* %cur_match.addr, align 4, !dbg !449
  %1 = load i32, i32* %cyclic_pos.addr, align 4, !dbg !450
  %idxprom = zext i32 %1 to i64, !dbg !451
  %2 = load i32*, i32** %son.addr, align 8, !dbg !451
  %arrayidx = getelementptr inbounds i32, i32* %2, i64 %idxprom, !dbg !451
  store i32 %0, i32* %arrayidx, align 4, !dbg !452
  br label %while.body, !dbg !453

while.body:                                       ; preds = %entry, %if.end44
  call void @llvm.dbg.declare(metadata i32* %delta, metadata !454, metadata !107), !dbg !456
  %3 = load i32, i32* %pos.addr, align 4, !dbg !457
  %4 = load i32, i32* %cur_match.addr, align 4, !dbg !458
  %sub = sub i32 %3, %4, !dbg !459
  store i32 %sub, i32* %delta, align 4, !dbg !456
  call void @llvm.dbg.declare(metadata i8** %pb, metadata !460, metadata !107), !dbg !461
  %5 = load i32, i32* %depth.addr, align 4, !dbg !462
  %dec = add i32 %5, -1, !dbg !462
  store i32 %dec, i32* %depth.addr, align 4, !dbg !462
  %cmp = icmp eq i32 %5, 0, !dbg !464
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !465

lor.lhs.false:                                    ; preds = %while.body
  %6 = load i32, i32* %delta, align 4, !dbg !466
  %7 = load i32, i32* %cyclic_size.addr, align 4, !dbg !468
  %cmp1 = icmp uge i32 %6, %7, !dbg !469
  br i1 %cmp1, label %if.then, label %if.end, !dbg !470

if.then:                                          ; preds = %lor.lhs.false, %while.body
  %8 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !471
  store %struct.lzma_match* %8, %struct.lzma_match** %retval, align 8, !dbg !472
  br label %return, !dbg !472

if.end:                                           ; preds = %lor.lhs.false
  %9 = load i8*, i8** %cur.addr, align 8, !dbg !473
  %10 = load i32, i32* %delta, align 4, !dbg !474
  %idx.ext = zext i32 %10 to i64, !dbg !475
  %idx.neg = sub i64 0, %idx.ext, !dbg !475
  %add.ptr = getelementptr inbounds i8, i8* %9, i64 %idx.neg, !dbg !475
  store i8* %add.ptr, i8** %pb, align 8, !dbg !476
  %11 = load i32, i32* %cyclic_pos.addr, align 4, !dbg !477
  %12 = load i32, i32* %delta, align 4, !dbg !478
  %sub2 = sub i32 %11, %12, !dbg !479
  %13 = load i32, i32* %delta, align 4, !dbg !480
  %14 = load i32, i32* %cyclic_pos.addr, align 4, !dbg !481
  %cmp3 = icmp ugt i32 %13, %14, !dbg !482
  br i1 %cmp3, label %cond.true, label %cond.false, !dbg !480

cond.true:                                        ; preds = %if.end
  %15 = load i32, i32* %cyclic_size.addr, align 4, !dbg !483
  br label %cond.end, !dbg !485

cond.false:                                       ; preds = %if.end
  br label %cond.end, !dbg !486

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %15, %cond.true ], [ 0, %cond.false ], !dbg !488
  %add = add i32 %sub2, %cond, !dbg !490
  %idxprom4 = zext i32 %add to i64, !dbg !491
  %16 = load i32*, i32** %son.addr, align 8, !dbg !491
  %arrayidx5 = getelementptr inbounds i32, i32* %16, i64 %idxprom4, !dbg !491
  %17 = load i32, i32* %arrayidx5, align 4, !dbg !491
  store i32 %17, i32* %cur_match.addr, align 4, !dbg !492
  %18 = load i32, i32* %len_best.addr, align 4, !dbg !493
  %idxprom6 = zext i32 %18 to i64, !dbg !495
  %19 = load i8*, i8** %pb, align 8, !dbg !495
  %arrayidx7 = getelementptr inbounds i8, i8* %19, i64 %idxprom6, !dbg !495
  %20 = load i8, i8* %arrayidx7, align 1, !dbg !495
  %conv = zext i8 %20 to i32, !dbg !495
  %21 = load i32, i32* %len_best.addr, align 4, !dbg !496
  %idxprom8 = zext i32 %21 to i64, !dbg !497
  %22 = load i8*, i8** %cur.addr, align 8, !dbg !497
  %arrayidx9 = getelementptr inbounds i8, i8* %22, i64 %idxprom8, !dbg !497
  %23 = load i8, i8* %arrayidx9, align 1, !dbg !497
  %conv10 = zext i8 %23 to i32, !dbg !497
  %cmp11 = icmp eq i32 %conv, %conv10, !dbg !498
  br i1 %cmp11, label %land.lhs.true, label %if.end44, !dbg !499

land.lhs.true:                                    ; preds = %cond.end
  %24 = load i8*, i8** %pb, align 8, !dbg !500
  %arrayidx13 = getelementptr inbounds i8, i8* %24, i64 0, !dbg !500
  %25 = load i8, i8* %arrayidx13, align 1, !dbg !500
  %conv14 = zext i8 %25 to i32, !dbg !500
  %26 = load i8*, i8** %cur.addr, align 8, !dbg !502
  %arrayidx15 = getelementptr inbounds i8, i8* %26, i64 0, !dbg !502
  %27 = load i8, i8* %arrayidx15, align 1, !dbg !502
  %conv16 = zext i8 %27 to i32, !dbg !502
  %cmp17 = icmp eq i32 %conv14, %conv16, !dbg !503
  br i1 %cmp17, label %if.then19, label %if.end44, !dbg !504

if.then19:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i32* %len, metadata !505, metadata !107), !dbg !507
  store i32 0, i32* %len, align 4, !dbg !507
  br label %while.cond20, !dbg !508

while.cond20:                                     ; preds = %if.end33, %if.then19
  %28 = load i32, i32* %len, align 4, !dbg !509
  %inc = add i32 %28, 1, !dbg !509
  store i32 %inc, i32* %len, align 4, !dbg !509
  %29 = load i32, i32* %len_limit.addr, align 4, !dbg !511
  %cmp21 = icmp ne i32 %inc, %29, !dbg !512
  br i1 %cmp21, label %while.body23, label %while.end, !dbg !513

while.body23:                                     ; preds = %while.cond20
  %30 = load i32, i32* %len, align 4, !dbg !514
  %idxprom24 = zext i32 %30 to i64, !dbg !516
  %31 = load i8*, i8** %pb, align 8, !dbg !516
  %arrayidx25 = getelementptr inbounds i8, i8* %31, i64 %idxprom24, !dbg !516
  %32 = load i8, i8* %arrayidx25, align 1, !dbg !516
  %conv26 = zext i8 %32 to i32, !dbg !516
  %33 = load i32, i32* %len, align 4, !dbg !517
  %idxprom27 = zext i32 %33 to i64, !dbg !518
  %34 = load i8*, i8** %cur.addr, align 8, !dbg !518
  %arrayidx28 = getelementptr inbounds i8, i8* %34, i64 %idxprom27, !dbg !518
  %35 = load i8, i8* %arrayidx28, align 1, !dbg !518
  %conv29 = zext i8 %35 to i32, !dbg !518
  %cmp30 = icmp ne i32 %conv26, %conv29, !dbg !519
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !520

if.then32:                                        ; preds = %while.body23
  br label %while.end, !dbg !521

if.end33:                                         ; preds = %while.body23
  br label %while.cond20, !dbg !522

while.end:                                        ; preds = %if.then32, %while.cond20
  %36 = load i32, i32* %len_best.addr, align 4, !dbg !524
  %37 = load i32, i32* %len, align 4, !dbg !526
  %cmp34 = icmp ult i32 %36, %37, !dbg !527
  br i1 %cmp34, label %if.then36, label %if.end43, !dbg !528

if.then36:                                        ; preds = %while.end
  %38 = load i32, i32* %len, align 4, !dbg !529
  store i32 %38, i32* %len_best.addr, align 4, !dbg !531
  %39 = load i32, i32* %len, align 4, !dbg !532
  %40 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !533
  %len37 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %40, i32 0, i32 0, !dbg !534
  store i32 %39, i32* %len37, align 4, !dbg !535
  %41 = load i32, i32* %delta, align 4, !dbg !536
  %sub38 = sub i32 %41, 1, !dbg !537
  %42 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !538
  %dist = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %42, i32 0, i32 1, !dbg !539
  store i32 %sub38, i32* %dist, align 4, !dbg !540
  %43 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !541
  %incdec.ptr = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %43, i32 1, !dbg !541
  store %struct.lzma_match* %incdec.ptr, %struct.lzma_match** %matches.addr, align 8, !dbg !541
  %44 = load i32, i32* %len, align 4, !dbg !542
  %45 = load i32, i32* %len_limit.addr, align 4, !dbg !544
  %cmp39 = icmp eq i32 %44, %45, !dbg !545
  br i1 %cmp39, label %if.then41, label %if.end42, !dbg !546

if.then41:                                        ; preds = %if.then36
  %46 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !547
  store %struct.lzma_match* %46, %struct.lzma_match** %retval, align 8, !dbg !548
  br label %return, !dbg !548

if.end42:                                         ; preds = %if.then36
  br label %if.end43, !dbg !549

if.end43:                                         ; preds = %if.end42, %while.end
  br label %if.end44, !dbg !550

if.end44:                                         ; preds = %if.end43, %land.lhs.true, %cond.end
  br label %while.body, !dbg !551

return:                                           ; preds = %if.then41, %if.then
  %47 = load %struct.lzma_match*, %struct.lzma_match** %retval, align 8, !dbg !553
  ret %struct.lzma_match* %47, !dbg !553
}

; Function Attrs: nounwind uwtable
define void @lzma_mf_hc3_skip(%struct.lzma_mf_s* %mf, i32 %amount) #0 !dbg !69 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %amount.addr = alloca i32, align 4
  %cur = alloca i8*, align 8
  %pos = alloca i32, align 4
  %temp = alloca i32, align 4
  %hash_value = alloca i32, align 4
  %hash_2_value = alloca i32, align 4
  %cur_match = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !554, metadata !107), !dbg !555
  store i32 %amount, i32* %amount.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %amount.addr, metadata !556, metadata !107), !dbg !557
  br label %do.body, !dbg !558

do.body:                                          ; preds = %do.cond, %entry
  call void @llvm.dbg.declare(metadata i8** %cur, metadata !559, metadata !107), !dbg !561
  call void @llvm.dbg.declare(metadata i32* %pos, metadata !562, metadata !107), !dbg !563
  call void @llvm.dbg.declare(metadata i32* %temp, metadata !564, metadata !107), !dbg !565
  call void @llvm.dbg.declare(metadata i32* %hash_value, metadata !566, metadata !107), !dbg !567
  call void @llvm.dbg.declare(metadata i32* %hash_2_value, metadata !568, metadata !107), !dbg !569
  call void @llvm.dbg.declare(metadata i32* %cur_match, metadata !570, metadata !107), !dbg !571
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !572
  %call = call i32 @mf_avail(%struct.lzma_mf_s* %0), !dbg !574
  %cmp = icmp ult i32 %call, 3, !dbg !575
  br i1 %cmp, label %if.then, label %if.end, !dbg !576

if.then:                                          ; preds = %do.body
  %1 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !577
  call void @move_pending(%struct.lzma_mf_s* %1), !dbg !579
  br label %do.cond, !dbg !580

if.end:                                           ; preds = %do.body
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !581
  %call1 = call i8* @mf_ptr(%struct.lzma_mf_s* %2), !dbg !582
  store i8* %call1, i8** %cur, align 8, !dbg !583
  %3 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !584
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %3, i32 0, i32 5, !dbg !585
  %4 = load i32, i32* %read_pos, align 8, !dbg !585
  %5 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !586
  %offset = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %5, i32 0, i32 4, !dbg !587
  %6 = load i32, i32* %offset, align 4, !dbg !587
  %add = add i32 %4, %6, !dbg !588
  store i32 %add, i32* %pos, align 4, !dbg !589
  %7 = load i8*, i8** %cur, align 8, !dbg !590
  %arrayidx = getelementptr inbounds i8, i8* %7, i64 0, !dbg !590
  %8 = load i8, i8* %arrayidx, align 1, !dbg !590
  %idxprom = zext i8 %8 to i64, !dbg !590
  %arrayidx2 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom, !dbg !590
  %9 = load i32, i32* %arrayidx2, align 4, !dbg !590
  %10 = load i8*, i8** %cur, align 8, !dbg !590
  %arrayidx3 = getelementptr inbounds i8, i8* %10, i64 1, !dbg !590
  %11 = load i8, i8* %arrayidx3, align 1, !dbg !590
  %conv = zext i8 %11 to i32, !dbg !590
  %xor = xor i32 %9, %conv, !dbg !590
  store i32 %xor, i32* %temp, align 4, !dbg !590
  %12 = load i32, i32* %temp, align 4, !dbg !590
  %and = and i32 %12, 1023, !dbg !590
  store i32 %and, i32* %hash_2_value, align 4, !dbg !590
  %13 = load i32, i32* %temp, align 4, !dbg !590
  %14 = load i8*, i8** %cur, align 8, !dbg !590
  %arrayidx4 = getelementptr inbounds i8, i8* %14, i64 2, !dbg !590
  %15 = load i8, i8* %arrayidx4, align 1, !dbg !590
  %conv5 = zext i8 %15 to i32, !dbg !590
  %shl = shl i32 %conv5, 8, !dbg !590
  %xor6 = xor i32 %13, %shl, !dbg !590
  %16 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !590
  %hash_mask = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %16, i32 0, i32 16, !dbg !590
  %17 = load i32, i32* %hash_mask, align 8, !dbg !590
  %and7 = and i32 %xor6, %17, !dbg !590
  store i32 %and7, i32* %hash_value, align 4, !dbg !590
  %18 = load i32, i32* %hash_value, align 4, !dbg !591
  %add8 = add i32 1024, %18, !dbg !592
  %idxprom9 = zext i32 %add8 to i64, !dbg !593
  %19 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !593
  %hash = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %19, i32 0, i32 12, !dbg !594
  %20 = load i32*, i32** %hash, align 8, !dbg !594
  %arrayidx10 = getelementptr inbounds i32, i32* %20, i64 %idxprom9, !dbg !593
  %21 = load i32, i32* %arrayidx10, align 4, !dbg !593
  store i32 %21, i32* %cur_match, align 4, !dbg !595
  %22 = load i32, i32* %pos, align 4, !dbg !596
  %23 = load i32, i32* %hash_2_value, align 4, !dbg !597
  %idxprom11 = zext i32 %23 to i64, !dbg !598
  %24 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !598
  %hash12 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %24, i32 0, i32 12, !dbg !599
  %25 = load i32*, i32** %hash12, align 8, !dbg !599
  %arrayidx13 = getelementptr inbounds i32, i32* %25, i64 %idxprom11, !dbg !598
  store i32 %22, i32* %arrayidx13, align 4, !dbg !600
  %26 = load i32, i32* %pos, align 4, !dbg !601
  %27 = load i32, i32* %hash_value, align 4, !dbg !602
  %add14 = add i32 1024, %27, !dbg !603
  %idxprom15 = zext i32 %add14 to i64, !dbg !604
  %28 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !604
  %hash16 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %28, i32 0, i32 12, !dbg !605
  %29 = load i32*, i32** %hash16, align 8, !dbg !605
  %arrayidx17 = getelementptr inbounds i32, i32* %29, i64 %idxprom15, !dbg !604
  store i32 %26, i32* %arrayidx17, align 4, !dbg !606
  br label %do.body18, !dbg !607

do.body18:                                        ; preds = %if.end
  %30 = load i32, i32* %cur_match, align 4, !dbg !608
  %31 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !608
  %cyclic_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %31, i32 0, i32 14, !dbg !608
  %32 = load i32, i32* %cyclic_pos, align 8, !dbg !608
  %idxprom19 = zext i32 %32 to i64, !dbg !608
  %33 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !608
  %son = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %33, i32 0, i32 13, !dbg !608
  %34 = load i32*, i32** %son, align 8, !dbg !608
  %arrayidx20 = getelementptr inbounds i32, i32* %34, i64 %idxprom19, !dbg !608
  store i32 %30, i32* %arrayidx20, align 4, !dbg !608
  %35 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !608
  call void @move_pos(%struct.lzma_mf_s* %35), !dbg !608
  br label %do.end, !dbg !608

do.end:                                           ; preds = %do.body18
  br label %do.cond, !dbg !611

do.cond:                                          ; preds = %do.end, %if.then
  %36 = load i32, i32* %amount.addr, align 4, !dbg !612
  %dec = add i32 %36, -1, !dbg !612
  store i32 %dec, i32* %amount.addr, align 4, !dbg !612
  %cmp21 = icmp ne i32 %dec, 0, !dbg !614
  br i1 %cmp21, label %do.body, label %do.end23, !dbg !615

do.end23:                                         ; preds = %do.cond
  ret void, !dbg !616
}

; Function Attrs: nounwind uwtable
define i32 @lzma_mf_hc4_find(%struct.lzma_mf_s* %mf, %struct.lzma_match* %matches) #0 !dbg !70 {
entry:
  %retval = alloca i32, align 4
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %matches.addr = alloca %struct.lzma_match*, align 8
  %cur = alloca i8*, align 8
  %pos = alloca i32, align 4
  %temp = alloca i32, align 4
  %hash_value = alloca i32, align 4
  %hash_2_value = alloca i32, align 4
  %hash_3_value = alloca i32, align 4
  %delta2 = alloca i32, align 4
  %delta3 = alloca i32, align 4
  %cur_match = alloca i32, align 4
  %len_best = alloca i32, align 4
  %matches_count = alloca i32, align 4
  %len_limit = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !617, metadata !107), !dbg !618
  store %struct.lzma_match* %matches, %struct.lzma_match** %matches.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_match** %matches.addr, metadata !619, metadata !107), !dbg !620
  call void @llvm.dbg.declare(metadata i8** %cur, metadata !621, metadata !107), !dbg !622
  call void @llvm.dbg.declare(metadata i32* %pos, metadata !623, metadata !107), !dbg !624
  call void @llvm.dbg.declare(metadata i32* %temp, metadata !625, metadata !107), !dbg !626
  call void @llvm.dbg.declare(metadata i32* %hash_value, metadata !627, metadata !107), !dbg !628
  call void @llvm.dbg.declare(metadata i32* %hash_2_value, metadata !629, metadata !107), !dbg !630
  call void @llvm.dbg.declare(metadata i32* %hash_3_value, metadata !631, metadata !107), !dbg !632
  call void @llvm.dbg.declare(metadata i32* %delta2, metadata !633, metadata !107), !dbg !634
  call void @llvm.dbg.declare(metadata i32* %delta3, metadata !635, metadata !107), !dbg !636
  call void @llvm.dbg.declare(metadata i32* %cur_match, metadata !637, metadata !107), !dbg !638
  call void @llvm.dbg.declare(metadata i32* %len_best, metadata !639, metadata !107), !dbg !640
  store i32 1, i32* %len_best, align 4, !dbg !640
  call void @llvm.dbg.declare(metadata i32* %matches_count, metadata !641, metadata !107), !dbg !642
  store i32 0, i32* %matches_count, align 4, !dbg !642
  call void @llvm.dbg.declare(metadata i32* %len_limit, metadata !643, metadata !107), !dbg !644
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !644
  %call = call i32 @mf_avail(%struct.lzma_mf_s* %0), !dbg !644
  store i32 %call, i32* %len_limit, align 4, !dbg !644
  %1 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !645
  %nice_len = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %1, i32 0, i32 18, !dbg !645
  %2 = load i32, i32* %nice_len, align 8, !dbg !645
  %3 = load i32, i32* %len_limit, align 4, !dbg !645
  %cmp = icmp ule i32 %2, %3, !dbg !645
  br i1 %cmp, label %if.then, label %if.else, !dbg !644

if.then:                                          ; preds = %entry
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !647
  %nice_len1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %4, i32 0, i32 18, !dbg !647
  %5 = load i32, i32* %nice_len1, align 8, !dbg !647
  store i32 %5, i32* %len_limit, align 4, !dbg !647
  br label %if.end5, !dbg !647

if.else:                                          ; preds = %entry
  %6 = load i32, i32* %len_limit, align 4, !dbg !650
  %cmp2 = icmp ult i32 %6, 4, !dbg !650
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !650

if.then3:                                         ; preds = %if.else
  %7 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !653
  %action = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %7, i32 0, i32 20, !dbg !653
  %8 = load i32, i32* %action, align 8, !dbg !653
  %cmp4 = icmp ne i32 %8, 0, !dbg !653
  br i1 %cmp4, label %cond.true, label %cond.false, !dbg !653

cond.true:                                        ; preds = %if.then3
  br label %cond.end, !dbg !656

cond.false:                                       ; preds = %if.then3
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.1, i32 0, i32 0), i32 394, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @__PRETTY_FUNCTION__.lzma_mf_hc4_find, i32 0, i32 0)) #5, !dbg !658
  unreachable, !dbg !658
                                                  ; No predecessors!
  br label %cond.end, !dbg !660

cond.end:                                         ; preds = %9, %cond.true
  %10 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !662
  call void @move_pending(%struct.lzma_mf_s* %10), !dbg !662
  store i32 0, i32* %retval, align 4, !dbg !662
  br label %do.end118, !dbg !662

if.end:                                           ; preds = %if.else
  br label %if.end5

if.end5:                                          ; preds = %if.end, %if.then
  %11 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !664
  %call6 = call i8* @mf_ptr(%struct.lzma_mf_s* %11), !dbg !664
  store i8* %call6, i8** %cur, align 8, !dbg !664
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !664
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %12, i32 0, i32 5, !dbg !664
  %13 = load i32, i32* %read_pos, align 8, !dbg !664
  %14 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !664
  %offset = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %14, i32 0, i32 4, !dbg !664
  %15 = load i32, i32* %offset, align 4, !dbg !664
  %add = add i32 %13, %15, !dbg !664
  store i32 %add, i32* %pos, align 4, !dbg !664
  %16 = load i8*, i8** %cur, align 8, !dbg !666
  %arrayidx = getelementptr inbounds i8, i8* %16, i64 0, !dbg !666
  %17 = load i8, i8* %arrayidx, align 1, !dbg !666
  %idxprom = zext i8 %17 to i64, !dbg !666
  %arrayidx7 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom, !dbg !666
  %18 = load i32, i32* %arrayidx7, align 4, !dbg !666
  %19 = load i8*, i8** %cur, align 8, !dbg !666
  %arrayidx8 = getelementptr inbounds i8, i8* %19, i64 1, !dbg !666
  %20 = load i8, i8* %arrayidx8, align 1, !dbg !666
  %conv = zext i8 %20 to i32, !dbg !666
  %xor = xor i32 %18, %conv, !dbg !666
  store i32 %xor, i32* %temp, align 4, !dbg !666
  %21 = load i32, i32* %temp, align 4, !dbg !666
  %and = and i32 %21, 1023, !dbg !666
  store i32 %and, i32* %hash_2_value, align 4, !dbg !666
  %22 = load i32, i32* %temp, align 4, !dbg !666
  %23 = load i8*, i8** %cur, align 8, !dbg !666
  %arrayidx9 = getelementptr inbounds i8, i8* %23, i64 2, !dbg !666
  %24 = load i8, i8* %arrayidx9, align 1, !dbg !666
  %conv10 = zext i8 %24 to i32, !dbg !666
  %shl = shl i32 %conv10, 8, !dbg !666
  %xor11 = xor i32 %22, %shl, !dbg !666
  %and12 = and i32 %xor11, 65535, !dbg !666
  store i32 %and12, i32* %hash_3_value, align 4, !dbg !666
  %25 = load i32, i32* %temp, align 4, !dbg !666
  %26 = load i8*, i8** %cur, align 8, !dbg !666
  %arrayidx13 = getelementptr inbounds i8, i8* %26, i64 2, !dbg !666
  %27 = load i8, i8* %arrayidx13, align 1, !dbg !666
  %conv14 = zext i8 %27 to i32, !dbg !666
  %shl15 = shl i32 %conv14, 8, !dbg !666
  %xor16 = xor i32 %25, %shl15, !dbg !666
  %28 = load i8*, i8** %cur, align 8, !dbg !666
  %arrayidx17 = getelementptr inbounds i8, i8* %28, i64 3, !dbg !666
  %29 = load i8, i8* %arrayidx17, align 1, !dbg !666
  %idxprom18 = zext i8 %29 to i64, !dbg !666
  %arrayidx19 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom18, !dbg !666
  %30 = load i32, i32* %arrayidx19, align 4, !dbg !666
  %shl20 = shl i32 %30, 5, !dbg !666
  %xor21 = xor i32 %xor16, %shl20, !dbg !666
  %31 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !666
  %hash_mask = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %31, i32 0, i32 16, !dbg !666
  %32 = load i32, i32* %hash_mask, align 8, !dbg !666
  %and22 = and i32 %xor21, %32, !dbg !666
  store i32 %and22, i32* %hash_value, align 4, !dbg !666
  %33 = load i32, i32* %pos, align 4, !dbg !667
  %34 = load i32, i32* %hash_2_value, align 4, !dbg !668
  %idxprom23 = zext i32 %34 to i64, !dbg !669
  %35 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !669
  %hash = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %35, i32 0, i32 12, !dbg !670
  %36 = load i32*, i32** %hash, align 8, !dbg !670
  %arrayidx24 = getelementptr inbounds i32, i32* %36, i64 %idxprom23, !dbg !669
  %37 = load i32, i32* %arrayidx24, align 4, !dbg !669
  %sub = sub i32 %33, %37, !dbg !671
  store i32 %sub, i32* %delta2, align 4, !dbg !672
  %38 = load i32, i32* %pos, align 4, !dbg !673
  %39 = load i32, i32* %hash_3_value, align 4, !dbg !674
  %add25 = add i32 1024, %39, !dbg !675
  %idxprom26 = zext i32 %add25 to i64, !dbg !676
  %40 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !676
  %hash27 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %40, i32 0, i32 12, !dbg !677
  %41 = load i32*, i32** %hash27, align 8, !dbg !677
  %arrayidx28 = getelementptr inbounds i32, i32* %41, i64 %idxprom26, !dbg !676
  %42 = load i32, i32* %arrayidx28, align 4, !dbg !676
  %sub29 = sub i32 %38, %42, !dbg !678
  store i32 %sub29, i32* %delta3, align 4, !dbg !679
  %43 = load i32, i32* %hash_value, align 4, !dbg !680
  %add30 = add i32 66560, %43, !dbg !681
  %idxprom31 = zext i32 %add30 to i64, !dbg !682
  %44 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !682
  %hash32 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %44, i32 0, i32 12, !dbg !683
  %45 = load i32*, i32** %hash32, align 8, !dbg !683
  %arrayidx33 = getelementptr inbounds i32, i32* %45, i64 %idxprom31, !dbg !682
  %46 = load i32, i32* %arrayidx33, align 4, !dbg !682
  store i32 %46, i32* %cur_match, align 4, !dbg !684
  %47 = load i32, i32* %pos, align 4, !dbg !685
  %48 = load i32, i32* %hash_2_value, align 4, !dbg !686
  %idxprom34 = zext i32 %48 to i64, !dbg !687
  %49 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !687
  %hash35 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %49, i32 0, i32 12, !dbg !688
  %50 = load i32*, i32** %hash35, align 8, !dbg !688
  %arrayidx36 = getelementptr inbounds i32, i32* %50, i64 %idxprom34, !dbg !687
  store i32 %47, i32* %arrayidx36, align 4, !dbg !689
  %51 = load i32, i32* %pos, align 4, !dbg !690
  %52 = load i32, i32* %hash_3_value, align 4, !dbg !691
  %add37 = add i32 1024, %52, !dbg !692
  %idxprom38 = zext i32 %add37 to i64, !dbg !693
  %53 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !693
  %hash39 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %53, i32 0, i32 12, !dbg !694
  %54 = load i32*, i32** %hash39, align 8, !dbg !694
  %arrayidx40 = getelementptr inbounds i32, i32* %54, i64 %idxprom38, !dbg !693
  store i32 %51, i32* %arrayidx40, align 4, !dbg !695
  %55 = load i32, i32* %pos, align 4, !dbg !696
  %56 = load i32, i32* %hash_value, align 4, !dbg !697
  %add41 = add i32 66560, %56, !dbg !698
  %idxprom42 = zext i32 %add41 to i64, !dbg !699
  %57 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !699
  %hash43 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %57, i32 0, i32 12, !dbg !700
  %58 = load i32*, i32** %hash43, align 8, !dbg !700
  %arrayidx44 = getelementptr inbounds i32, i32* %58, i64 %idxprom42, !dbg !699
  store i32 %55, i32* %arrayidx44, align 4, !dbg !701
  %59 = load i32, i32* %delta2, align 4, !dbg !702
  %60 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !704
  %cyclic_size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %60, i32 0, i32 15, !dbg !705
  %61 = load i32, i32* %cyclic_size, align 4, !dbg !705
  %cmp45 = icmp ult i32 %59, %61, !dbg !706
  br i1 %cmp45, label %land.lhs.true, label %if.end55, !dbg !707

land.lhs.true:                                    ; preds = %if.end5
  %62 = load i8*, i8** %cur, align 8, !dbg !708
  %63 = load i32, i32* %delta2, align 4, !dbg !710
  %idx.ext = zext i32 %63 to i64, !dbg !711
  %idx.neg = sub i64 0, %idx.ext, !dbg !711
  %add.ptr = getelementptr inbounds i8, i8* %62, i64 %idx.neg, !dbg !711
  %64 = load i8, i8* %add.ptr, align 1, !dbg !712
  %conv47 = zext i8 %64 to i32, !dbg !712
  %65 = load i8*, i8** %cur, align 8, !dbg !713
  %66 = load i8, i8* %65, align 1, !dbg !714
  %conv48 = zext i8 %66 to i32, !dbg !714
  %cmp49 = icmp eq i32 %conv47, %conv48, !dbg !715
  br i1 %cmp49, label %if.then51, label %if.end55, !dbg !716

if.then51:                                        ; preds = %land.lhs.true
  store i32 2, i32* %len_best, align 4, !dbg !717
  %67 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !719
  %arrayidx52 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %67, i64 0, !dbg !719
  %len = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx52, i32 0, i32 0, !dbg !720
  store i32 2, i32* %len, align 4, !dbg !721
  %68 = load i32, i32* %delta2, align 4, !dbg !722
  %sub53 = sub i32 %68, 1, !dbg !723
  %69 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !724
  %arrayidx54 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %69, i64 0, !dbg !724
  %dist = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx54, i32 0, i32 1, !dbg !725
  store i32 %sub53, i32* %dist, align 4, !dbg !726
  store i32 1, i32* %matches_count, align 4, !dbg !727
  br label %if.end55, !dbg !728

if.end55:                                         ; preds = %if.then51, %land.lhs.true, %if.end5
  %70 = load i32, i32* %delta2, align 4, !dbg !729
  %71 = load i32, i32* %delta3, align 4, !dbg !731
  %cmp56 = icmp ne i32 %70, %71, !dbg !732
  br i1 %cmp56, label %land.lhs.true58, label %if.end75, !dbg !733

land.lhs.true58:                                  ; preds = %if.end55
  %72 = load i32, i32* %delta3, align 4, !dbg !734
  %73 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !736
  %cyclic_size59 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %73, i32 0, i32 15, !dbg !737
  %74 = load i32, i32* %cyclic_size59, align 4, !dbg !737
  %cmp60 = icmp ult i32 %72, %74, !dbg !738
  br i1 %cmp60, label %land.lhs.true62, label %if.end75, !dbg !739

land.lhs.true62:                                  ; preds = %land.lhs.true58
  %75 = load i8*, i8** %cur, align 8, !dbg !740
  %76 = load i32, i32* %delta3, align 4, !dbg !741
  %idx.ext63 = zext i32 %76 to i64, !dbg !742
  %idx.neg64 = sub i64 0, %idx.ext63, !dbg !742
  %add.ptr65 = getelementptr inbounds i8, i8* %75, i64 %idx.neg64, !dbg !742
  %77 = load i8, i8* %add.ptr65, align 1, !dbg !743
  %conv66 = zext i8 %77 to i32, !dbg !743
  %78 = load i8*, i8** %cur, align 8, !dbg !744
  %79 = load i8, i8* %78, align 1, !dbg !745
  %conv67 = zext i8 %79 to i32, !dbg !745
  %cmp68 = icmp eq i32 %conv66, %conv67, !dbg !746
  br i1 %cmp68, label %if.then70, label %if.end75, !dbg !747

if.then70:                                        ; preds = %land.lhs.true62
  store i32 3, i32* %len_best, align 4, !dbg !749
  %80 = load i32, i32* %delta3, align 4, !dbg !751
  %sub71 = sub i32 %80, 1, !dbg !752
  %81 = load i32, i32* %matches_count, align 4, !dbg !753
  %inc = add i32 %81, 1, !dbg !753
  store i32 %inc, i32* %matches_count, align 4, !dbg !753
  %idxprom72 = zext i32 %81 to i64, !dbg !754
  %82 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !754
  %arrayidx73 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %82, i64 %idxprom72, !dbg !754
  %dist74 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx73, i32 0, i32 1, !dbg !755
  store i32 %sub71, i32* %dist74, align 4, !dbg !756
  %83 = load i32, i32* %delta3, align 4, !dbg !757
  store i32 %83, i32* %delta2, align 4, !dbg !758
  br label %if.end75, !dbg !759

if.end75:                                         ; preds = %if.then70, %land.lhs.true62, %land.lhs.true58, %if.end55
  %84 = load i32, i32* %matches_count, align 4, !dbg !760
  %cmp76 = icmp ne i32 %84, 0, !dbg !762
  br i1 %cmp76, label %if.then78, label %if.end105, !dbg !763

if.then78:                                        ; preds = %if.end75
  br label %for.cond, !dbg !764

for.cond:                                         ; preds = %for.inc, %if.then78
  %85 = load i32, i32* %len_best, align 4, !dbg !766
  %86 = load i32, i32* %len_limit, align 4, !dbg !770
  %cmp79 = icmp ne i32 %85, %86, !dbg !771
  br i1 %cmp79, label %for.body, label %for.end, !dbg !772

for.body:                                         ; preds = %for.cond
  %87 = load i8*, i8** %cur, align 8, !dbg !773
  %88 = load i32, i32* %len_best, align 4, !dbg !775
  %idx.ext81 = zext i32 %88 to i64, !dbg !776
  %add.ptr82 = getelementptr inbounds i8, i8* %87, i64 %idx.ext81, !dbg !776
  %89 = load i32, i32* %delta2, align 4, !dbg !777
  %idx.ext83 = zext i32 %89 to i64, !dbg !778
  %idx.neg84 = sub i64 0, %idx.ext83, !dbg !778
  %add.ptr85 = getelementptr inbounds i8, i8* %add.ptr82, i64 %idx.neg84, !dbg !778
  %90 = load i8, i8* %add.ptr85, align 1, !dbg !779
  %conv86 = zext i8 %90 to i32, !dbg !779
  %91 = load i32, i32* %len_best, align 4, !dbg !780
  %idxprom87 = zext i32 %91 to i64, !dbg !781
  %92 = load i8*, i8** %cur, align 8, !dbg !781
  %arrayidx88 = getelementptr inbounds i8, i8* %92, i64 %idxprom87, !dbg !781
  %93 = load i8, i8* %arrayidx88, align 1, !dbg !781
  %conv89 = zext i8 %93 to i32, !dbg !781
  %cmp90 = icmp ne i32 %conv86, %conv89, !dbg !782
  br i1 %cmp90, label %if.then92, label %if.end93, !dbg !783

if.then92:                                        ; preds = %for.body
  br label %for.end, !dbg !784

if.end93:                                         ; preds = %for.body
  br label %for.inc, !dbg !785

for.inc:                                          ; preds = %if.end93
  %94 = load i32, i32* %len_best, align 4, !dbg !787
  %inc94 = add i32 %94, 1, !dbg !787
  store i32 %inc94, i32* %len_best, align 4, !dbg !787
  br label %for.cond, !dbg !789

for.end:                                          ; preds = %if.then92, %for.cond
  %95 = load i32, i32* %len_best, align 4, !dbg !790
  %96 = load i32, i32* %matches_count, align 4, !dbg !791
  %sub95 = sub i32 %96, 1, !dbg !792
  %idxprom96 = zext i32 %sub95 to i64, !dbg !793
  %97 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !793
  %arrayidx97 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %97, i64 %idxprom96, !dbg !793
  %len98 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx97, i32 0, i32 0, !dbg !794
  store i32 %95, i32* %len98, align 4, !dbg !795
  %98 = load i32, i32* %len_best, align 4, !dbg !796
  %99 = load i32, i32* %len_limit, align 4, !dbg !798
  %cmp99 = icmp eq i32 %98, %99, !dbg !799
  br i1 %cmp99, label %if.then101, label %if.end104, !dbg !800

if.then101:                                       ; preds = %for.end
  br label %do.body, !dbg !801

do.body:                                          ; preds = %if.then101
  %100 = load i32, i32* %cur_match, align 4, !dbg !803
  %101 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !803
  %cyclic_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %101, i32 0, i32 14, !dbg !803
  %102 = load i32, i32* %cyclic_pos, align 8, !dbg !803
  %idxprom102 = zext i32 %102 to i64, !dbg !803
  %103 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !803
  %son = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %103, i32 0, i32 13, !dbg !803
  %104 = load i32*, i32** %son, align 8, !dbg !803
  %arrayidx103 = getelementptr inbounds i32, i32* %104, i64 %idxprom102, !dbg !803
  store i32 %100, i32* %arrayidx103, align 4, !dbg !803
  %105 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !803
  call void @move_pos(%struct.lzma_mf_s* %105), !dbg !803
  br label %do.end, !dbg !803

do.end:                                           ; preds = %do.body
  %106 = load i32, i32* %matches_count, align 4, !dbg !806
  store i32 %106, i32* %retval, align 4, !dbg !807
  br label %do.end118, !dbg !807

if.end104:                                        ; preds = %for.end
  br label %if.end105, !dbg !808

if.end105:                                        ; preds = %if.end104, %if.end75
  %107 = load i32, i32* %len_best, align 4, !dbg !809
  %cmp106 = icmp ult i32 %107, 3, !dbg !811
  br i1 %cmp106, label %if.then108, label %if.end109, !dbg !812

if.then108:                                       ; preds = %if.end105
  store i32 3, i32* %len_best, align 4, !dbg !813
  br label %if.end109, !dbg !814

if.end109:                                        ; preds = %if.then108, %if.end105
  br label %do.body110, !dbg !815

do.body110:                                       ; preds = %if.end109
  %108 = load i32, i32* %len_limit, align 4, !dbg !816
  %109 = load i32, i32* %pos, align 4, !dbg !816
  %110 = load i8*, i8** %cur, align 8, !dbg !816
  %111 = load i32, i32* %cur_match, align 4, !dbg !816
  %112 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !816
  %depth = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %112, i32 0, i32 17, !dbg !816
  %113 = load i32, i32* %depth, align 4, !dbg !816
  %114 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !816
  %son111 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %114, i32 0, i32 13, !dbg !816
  %115 = load i32*, i32** %son111, align 8, !dbg !816
  %116 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !816
  %cyclic_pos112 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %116, i32 0, i32 14, !dbg !816
  %117 = load i32, i32* %cyclic_pos112, align 8, !dbg !816
  %118 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !816
  %cyclic_size113 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %118, i32 0, i32 15, !dbg !816
  %119 = load i32, i32* %cyclic_size113, align 4, !dbg !816
  %120 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !816
  %121 = load i32, i32* %matches_count, align 4, !dbg !816
  %idx.ext114 = zext i32 %121 to i64, !dbg !816
  %add.ptr115 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %120, i64 %idx.ext114, !dbg !816
  %122 = load i32, i32* %len_best, align 4, !dbg !816
  %call116 = call %struct.lzma_match* @hc_find_func(i32 %108, i32 %109, i8* %110, i32 %111, i32 %113, i32* %115, i32 %117, i32 %119, %struct.lzma_match* %add.ptr115, i32 %122), !dbg !816
  %123 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !816
  %sub.ptr.lhs.cast = ptrtoint %struct.lzma_match* %call116 to i64, !dbg !816
  %sub.ptr.rhs.cast = ptrtoint %struct.lzma_match* %123 to i64, !dbg !816
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !816
  %sub.ptr.div = sdiv exact i64 %sub.ptr.sub, 8, !dbg !816
  %conv117 = trunc i64 %sub.ptr.div to i32, !dbg !816
  store i32 %conv117, i32* %matches_count, align 4, !dbg !816
  %124 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !816
  call void @move_pos(%struct.lzma_mf_s* %124), !dbg !819
  %125 = load i32, i32* %matches_count, align 4, !dbg !816
  store i32 %125, i32* %retval, align 4, !dbg !816
  br label %do.end118, !dbg !816

do.end118:                                        ; preds = %cond.end, %do.end, %do.body110
  %126 = load i32, i32* %retval, align 4, !dbg !821
  ret i32 %126, !dbg !821
}

; Function Attrs: nounwind uwtable
define void @lzma_mf_hc4_skip(%struct.lzma_mf_s* %mf, i32 %amount) #0 !dbg !71 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %amount.addr = alloca i32, align 4
  %cur = alloca i8*, align 8
  %pos = alloca i32, align 4
  %temp = alloca i32, align 4
  %hash_value = alloca i32, align 4
  %hash_2_value = alloca i32, align 4
  %hash_3_value = alloca i32, align 4
  %cur_match = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !822, metadata !107), !dbg !823
  store i32 %amount, i32* %amount.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %amount.addr, metadata !824, metadata !107), !dbg !825
  br label %do.body, !dbg !826

do.body:                                          ; preds = %do.cond, %entry
  call void @llvm.dbg.declare(metadata i8** %cur, metadata !827, metadata !107), !dbg !829
  call void @llvm.dbg.declare(metadata i32* %pos, metadata !830, metadata !107), !dbg !831
  call void @llvm.dbg.declare(metadata i32* %temp, metadata !832, metadata !107), !dbg !833
  call void @llvm.dbg.declare(metadata i32* %hash_value, metadata !834, metadata !107), !dbg !835
  call void @llvm.dbg.declare(metadata i32* %hash_2_value, metadata !836, metadata !107), !dbg !837
  call void @llvm.dbg.declare(metadata i32* %hash_3_value, metadata !838, metadata !107), !dbg !839
  call void @llvm.dbg.declare(metadata i32* %cur_match, metadata !840, metadata !107), !dbg !841
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !842
  %call = call i32 @mf_avail(%struct.lzma_mf_s* %0), !dbg !844
  %cmp = icmp ult i32 %call, 4, !dbg !845
  br i1 %cmp, label %if.then, label %if.end, !dbg !846

if.then:                                          ; preds = %do.body
  %1 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !847
  call void @move_pending(%struct.lzma_mf_s* %1), !dbg !849
  br label %do.cond, !dbg !850

if.end:                                           ; preds = %do.body
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !851
  %call1 = call i8* @mf_ptr(%struct.lzma_mf_s* %2), !dbg !852
  store i8* %call1, i8** %cur, align 8, !dbg !853
  %3 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !854
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %3, i32 0, i32 5, !dbg !855
  %4 = load i32, i32* %read_pos, align 8, !dbg !855
  %5 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !856
  %offset = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %5, i32 0, i32 4, !dbg !857
  %6 = load i32, i32* %offset, align 4, !dbg !857
  %add = add i32 %4, %6, !dbg !858
  store i32 %add, i32* %pos, align 4, !dbg !859
  %7 = load i8*, i8** %cur, align 8, !dbg !860
  %arrayidx = getelementptr inbounds i8, i8* %7, i64 0, !dbg !860
  %8 = load i8, i8* %arrayidx, align 1, !dbg !860
  %idxprom = zext i8 %8 to i64, !dbg !860
  %arrayidx2 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom, !dbg !860
  %9 = load i32, i32* %arrayidx2, align 4, !dbg !860
  %10 = load i8*, i8** %cur, align 8, !dbg !860
  %arrayidx3 = getelementptr inbounds i8, i8* %10, i64 1, !dbg !860
  %11 = load i8, i8* %arrayidx3, align 1, !dbg !860
  %conv = zext i8 %11 to i32, !dbg !860
  %xor = xor i32 %9, %conv, !dbg !860
  store i32 %xor, i32* %temp, align 4, !dbg !860
  %12 = load i32, i32* %temp, align 4, !dbg !860
  %and = and i32 %12, 1023, !dbg !860
  store i32 %and, i32* %hash_2_value, align 4, !dbg !860
  %13 = load i32, i32* %temp, align 4, !dbg !860
  %14 = load i8*, i8** %cur, align 8, !dbg !860
  %arrayidx4 = getelementptr inbounds i8, i8* %14, i64 2, !dbg !860
  %15 = load i8, i8* %arrayidx4, align 1, !dbg !860
  %conv5 = zext i8 %15 to i32, !dbg !860
  %shl = shl i32 %conv5, 8, !dbg !860
  %xor6 = xor i32 %13, %shl, !dbg !860
  %and7 = and i32 %xor6, 65535, !dbg !860
  store i32 %and7, i32* %hash_3_value, align 4, !dbg !860
  %16 = load i32, i32* %temp, align 4, !dbg !860
  %17 = load i8*, i8** %cur, align 8, !dbg !860
  %arrayidx8 = getelementptr inbounds i8, i8* %17, i64 2, !dbg !860
  %18 = load i8, i8* %arrayidx8, align 1, !dbg !860
  %conv9 = zext i8 %18 to i32, !dbg !860
  %shl10 = shl i32 %conv9, 8, !dbg !860
  %xor11 = xor i32 %16, %shl10, !dbg !860
  %19 = load i8*, i8** %cur, align 8, !dbg !860
  %arrayidx12 = getelementptr inbounds i8, i8* %19, i64 3, !dbg !860
  %20 = load i8, i8* %arrayidx12, align 1, !dbg !860
  %idxprom13 = zext i8 %20 to i64, !dbg !860
  %arrayidx14 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom13, !dbg !860
  %21 = load i32, i32* %arrayidx14, align 4, !dbg !860
  %shl15 = shl i32 %21, 5, !dbg !860
  %xor16 = xor i32 %xor11, %shl15, !dbg !860
  %22 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !860
  %hash_mask = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %22, i32 0, i32 16, !dbg !860
  %23 = load i32, i32* %hash_mask, align 8, !dbg !860
  %and17 = and i32 %xor16, %23, !dbg !860
  store i32 %and17, i32* %hash_value, align 4, !dbg !860
  %24 = load i32, i32* %hash_value, align 4, !dbg !861
  %add18 = add i32 66560, %24, !dbg !862
  %idxprom19 = zext i32 %add18 to i64, !dbg !863
  %25 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !863
  %hash = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %25, i32 0, i32 12, !dbg !864
  %26 = load i32*, i32** %hash, align 8, !dbg !864
  %arrayidx20 = getelementptr inbounds i32, i32* %26, i64 %idxprom19, !dbg !863
  %27 = load i32, i32* %arrayidx20, align 4, !dbg !863
  store i32 %27, i32* %cur_match, align 4, !dbg !865
  %28 = load i32, i32* %pos, align 4, !dbg !866
  %29 = load i32, i32* %hash_2_value, align 4, !dbg !867
  %idxprom21 = zext i32 %29 to i64, !dbg !868
  %30 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !868
  %hash22 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %30, i32 0, i32 12, !dbg !869
  %31 = load i32*, i32** %hash22, align 8, !dbg !869
  %arrayidx23 = getelementptr inbounds i32, i32* %31, i64 %idxprom21, !dbg !868
  store i32 %28, i32* %arrayidx23, align 4, !dbg !870
  %32 = load i32, i32* %pos, align 4, !dbg !871
  %33 = load i32, i32* %hash_3_value, align 4, !dbg !872
  %add24 = add i32 1024, %33, !dbg !873
  %idxprom25 = zext i32 %add24 to i64, !dbg !874
  %34 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !874
  %hash26 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %34, i32 0, i32 12, !dbg !875
  %35 = load i32*, i32** %hash26, align 8, !dbg !875
  %arrayidx27 = getelementptr inbounds i32, i32* %35, i64 %idxprom25, !dbg !874
  store i32 %32, i32* %arrayidx27, align 4, !dbg !876
  %36 = load i32, i32* %pos, align 4, !dbg !877
  %37 = load i32, i32* %hash_value, align 4, !dbg !878
  %add28 = add i32 66560, %37, !dbg !879
  %idxprom29 = zext i32 %add28 to i64, !dbg !880
  %38 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !880
  %hash30 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %38, i32 0, i32 12, !dbg !881
  %39 = load i32*, i32** %hash30, align 8, !dbg !881
  %arrayidx31 = getelementptr inbounds i32, i32* %39, i64 %idxprom29, !dbg !880
  store i32 %36, i32* %arrayidx31, align 4, !dbg !882
  br label %do.body32, !dbg !883

do.body32:                                        ; preds = %if.end
  %40 = load i32, i32* %cur_match, align 4, !dbg !884
  %41 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !884
  %cyclic_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %41, i32 0, i32 14, !dbg !884
  %42 = load i32, i32* %cyclic_pos, align 8, !dbg !884
  %idxprom33 = zext i32 %42 to i64, !dbg !884
  %43 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !884
  %son = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %43, i32 0, i32 13, !dbg !884
  %44 = load i32*, i32** %son, align 8, !dbg !884
  %arrayidx34 = getelementptr inbounds i32, i32* %44, i64 %idxprom33, !dbg !884
  store i32 %40, i32* %arrayidx34, align 4, !dbg !884
  %45 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !884
  call void @move_pos(%struct.lzma_mf_s* %45), !dbg !884
  br label %do.end, !dbg !884

do.end:                                           ; preds = %do.body32
  br label %do.cond, !dbg !887

do.cond:                                          ; preds = %do.end, %if.then
  %46 = load i32, i32* %amount.addr, align 4, !dbg !888
  %dec = add i32 %46, -1, !dbg !888
  store i32 %dec, i32* %amount.addr, align 4, !dbg !888
  %cmp35 = icmp ne i32 %dec, 0, !dbg !890
  br i1 %cmp35, label %do.body, label %do.end37, !dbg !891

do.end37:                                         ; preds = %do.cond
  ret void, !dbg !892
}

; Function Attrs: nounwind uwtable
define i32 @lzma_mf_bt2_find(%struct.lzma_mf_s* %mf, %struct.lzma_match* %matches) #0 !dbg !72 {
entry:
  %retval = alloca i32, align 4
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %matches.addr = alloca %struct.lzma_match*, align 8
  %cur = alloca i8*, align 8
  %pos = alloca i32, align 4
  %hash_value = alloca i32, align 4
  %cur_match = alloca i32, align 4
  %matches_count = alloca i32, align 4
  %len_limit = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !893, metadata !107), !dbg !894
  store %struct.lzma_match* %matches, %struct.lzma_match** %matches.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_match** %matches.addr, metadata !895, metadata !107), !dbg !896
  call void @llvm.dbg.declare(metadata i8** %cur, metadata !897, metadata !107), !dbg !898
  call void @llvm.dbg.declare(metadata i32* %pos, metadata !899, metadata !107), !dbg !900
  call void @llvm.dbg.declare(metadata i32* %hash_value, metadata !901, metadata !107), !dbg !902
  call void @llvm.dbg.declare(metadata i32* %cur_match, metadata !903, metadata !107), !dbg !904
  call void @llvm.dbg.declare(metadata i32* %matches_count, metadata !905, metadata !107), !dbg !906
  store i32 0, i32* %matches_count, align 4, !dbg !906
  call void @llvm.dbg.declare(metadata i32* %len_limit, metadata !907, metadata !107), !dbg !908
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !908
  %call = call i32 @mf_avail(%struct.lzma_mf_s* %0), !dbg !908
  store i32 %call, i32* %len_limit, align 4, !dbg !908
  %1 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !909
  %nice_len = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %1, i32 0, i32 18, !dbg !909
  %2 = load i32, i32* %nice_len, align 8, !dbg !909
  %3 = load i32, i32* %len_limit, align 4, !dbg !909
  %cmp = icmp ule i32 %2, %3, !dbg !909
  br i1 %cmp, label %if.then, label %if.else, !dbg !908

if.then:                                          ; preds = %entry
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !911
  %nice_len1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %4, i32 0, i32 18, !dbg !911
  %5 = load i32, i32* %nice_len1, align 8, !dbg !911
  store i32 %5, i32* %len_limit, align 4, !dbg !911
  br label %if.end7, !dbg !911

if.else:                                          ; preds = %entry
  %6 = load i32, i32* %len_limit, align 4, !dbg !914
  %cmp2 = icmp ult i32 %6, 2, !dbg !914
  br i1 %cmp2, label %if.then4, label %lor.lhs.false, !dbg !914

lor.lhs.false:                                    ; preds = %if.else
  %7 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !917
  %action = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %7, i32 0, i32 20, !dbg !917
  %8 = load i32, i32* %action, align 8, !dbg !917
  %cmp3 = icmp eq i32 %8, 1, !dbg !917
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !917

if.then4:                                         ; preds = %lor.lhs.false, %if.else
  %9 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !919
  %action5 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %9, i32 0, i32 20, !dbg !919
  %10 = load i32, i32* %action5, align 8, !dbg !919
  %cmp6 = icmp ne i32 %10, 0, !dbg !919
  br i1 %cmp6, label %cond.true, label %cond.false, !dbg !919

cond.true:                                        ; preds = %if.then4
  br label %cond.end, !dbg !922

cond.false:                                       ; preds = %if.then4
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.1, i32 0, i32 0), i32 635, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @__PRETTY_FUNCTION__.lzma_mf_bt2_find, i32 0, i32 0)) #5, !dbg !924
  unreachable, !dbg !924
                                                  ; No predecessors!
  br label %cond.end, !dbg !926

cond.end:                                         ; preds = %11, %cond.true
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !928
  call void @move_pending(%struct.lzma_mf_s* %12), !dbg !928
  store i32 0, i32* %retval, align 4, !dbg !928
  br label %do.end, !dbg !928

if.end:                                           ; preds = %lor.lhs.false
  br label %if.end7

if.end7:                                          ; preds = %if.end, %if.then
  %13 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !930
  %call8 = call i8* @mf_ptr(%struct.lzma_mf_s* %13), !dbg !930
  store i8* %call8, i8** %cur, align 8, !dbg !930
  %14 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !930
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %14, i32 0, i32 5, !dbg !930
  %15 = load i32, i32* %read_pos, align 8, !dbg !930
  %16 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !930
  %offset = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %16, i32 0, i32 4, !dbg !930
  %17 = load i32, i32* %offset, align 4, !dbg !930
  %add = add i32 %15, %17, !dbg !930
  store i32 %add, i32* %pos, align 4, !dbg !930
  %18 = load i8*, i8** %cur, align 8, !dbg !932
  %19 = bitcast i8* %18 to i16*, !dbg !932
  %20 = load i16, i16* %19, align 2, !dbg !932
  %conv = zext i16 %20 to i32, !dbg !932
  store i32 %conv, i32* %hash_value, align 4, !dbg !932
  %21 = load i32, i32* %hash_value, align 4, !dbg !933
  %idxprom = zext i32 %21 to i64, !dbg !934
  %22 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !934
  %hash = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %22, i32 0, i32 12, !dbg !935
  %23 = load i32*, i32** %hash, align 8, !dbg !935
  %arrayidx = getelementptr inbounds i32, i32* %23, i64 %idxprom, !dbg !934
  %24 = load i32, i32* %arrayidx, align 4, !dbg !934
  store i32 %24, i32* %cur_match, align 4, !dbg !936
  %25 = load i32, i32* %pos, align 4, !dbg !937
  %26 = load i32, i32* %hash_value, align 4, !dbg !938
  %idxprom9 = zext i32 %26 to i64, !dbg !939
  %27 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !939
  %hash10 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %27, i32 0, i32 12, !dbg !940
  %28 = load i32*, i32** %hash10, align 8, !dbg !940
  %arrayidx11 = getelementptr inbounds i32, i32* %28, i64 %idxprom9, !dbg !939
  store i32 %25, i32* %arrayidx11, align 4, !dbg !941
  br label %do.body, !dbg !942

do.body:                                          ; preds = %if.end7
  %29 = load i32, i32* %len_limit, align 4, !dbg !943
  %30 = load i32, i32* %pos, align 4, !dbg !943
  %31 = load i8*, i8** %cur, align 8, !dbg !943
  %32 = load i32, i32* %cur_match, align 4, !dbg !943
  %33 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !943
  %depth = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %33, i32 0, i32 17, !dbg !943
  %34 = load i32, i32* %depth, align 4, !dbg !943
  %35 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !943
  %son = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %35, i32 0, i32 13, !dbg !943
  %36 = load i32*, i32** %son, align 8, !dbg !943
  %37 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !943
  %cyclic_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %37, i32 0, i32 14, !dbg !943
  %38 = load i32, i32* %cyclic_pos, align 8, !dbg !943
  %39 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !943
  %cyclic_size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %39, i32 0, i32 15, !dbg !943
  %40 = load i32, i32* %cyclic_size, align 4, !dbg !943
  %41 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !943
  %42 = load i32, i32* %matches_count, align 4, !dbg !943
  %idx.ext = zext i32 %42 to i64, !dbg !943
  %add.ptr = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %41, i64 %idx.ext, !dbg !943
  %call12 = call %struct.lzma_match* @bt_find_func(i32 %29, i32 %30, i8* %31, i32 %32, i32 %34, i32* %36, i32 %38, i32 %40, %struct.lzma_match* %add.ptr, i32 1), !dbg !943
  %43 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !943
  %sub.ptr.lhs.cast = ptrtoint %struct.lzma_match* %call12 to i64, !dbg !943
  %sub.ptr.rhs.cast = ptrtoint %struct.lzma_match* %43 to i64, !dbg !943
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !943
  %sub.ptr.div = sdiv exact i64 %sub.ptr.sub, 8, !dbg !943
  %conv13 = trunc i64 %sub.ptr.div to i32, !dbg !943
  store i32 %conv13, i32* %matches_count, align 4, !dbg !943
  %44 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !943
  call void @move_pos(%struct.lzma_mf_s* %44), !dbg !946
  %45 = load i32, i32* %matches_count, align 4, !dbg !943
  store i32 %45, i32* %retval, align 4, !dbg !943
  br label %do.end, !dbg !943

do.end:                                           ; preds = %cond.end, %do.body
  %46 = load i32, i32* %retval, align 4, !dbg !948
  ret i32 %46, !dbg !948
}

; Function Attrs: nounwind uwtable
define internal %struct.lzma_match* @bt_find_func(i32 %len_limit, i32 %pos, i8* %cur, i32 %cur_match, i32 %depth, i32* %son, i32 %cyclic_pos, i32 %cyclic_size, %struct.lzma_match* %matches, i32 %len_best) #0 !dbg !99 {
entry:
  %retval = alloca %struct.lzma_match*, align 8
  %len_limit.addr = alloca i32, align 4
  %pos.addr = alloca i32, align 4
  %cur.addr = alloca i8*, align 8
  %cur_match.addr = alloca i32, align 4
  %depth.addr = alloca i32, align 4
  %son.addr = alloca i32*, align 8
  %cyclic_pos.addr = alloca i32, align 4
  %cyclic_size.addr = alloca i32, align 4
  %matches.addr = alloca %struct.lzma_match*, align 8
  %len_best.addr = alloca i32, align 4
  %ptr0 = alloca i32*, align 8
  %ptr1 = alloca i32*, align 8
  %len0 = alloca i32, align 4
  %len1 = alloca i32, align 4
  %pair = alloca i32*, align 8
  %pb = alloca i8*, align 8
  %len = alloca i32, align 4
  %delta = alloca i32, align 4
  store i32 %len_limit, i32* %len_limit.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len_limit.addr, metadata !949, metadata !107), !dbg !950
  store i32 %pos, i32* %pos.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos.addr, metadata !951, metadata !107), !dbg !952
  store i8* %cur, i8** %cur.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cur.addr, metadata !953, metadata !107), !dbg !954
  store i32 %cur_match, i32* %cur_match.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %cur_match.addr, metadata !955, metadata !107), !dbg !956
  store i32 %depth, i32* %depth.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %depth.addr, metadata !957, metadata !107), !dbg !958
  store i32* %son, i32** %son.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %son.addr, metadata !959, metadata !107), !dbg !960
  store i32 %cyclic_pos, i32* %cyclic_pos.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %cyclic_pos.addr, metadata !961, metadata !107), !dbg !962
  store i32 %cyclic_size, i32* %cyclic_size.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %cyclic_size.addr, metadata !963, metadata !107), !dbg !964
  store %struct.lzma_match* %matches, %struct.lzma_match** %matches.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_match** %matches.addr, metadata !965, metadata !107), !dbg !966
  store i32 %len_best, i32* %len_best.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len_best.addr, metadata !967, metadata !107), !dbg !968
  call void @llvm.dbg.declare(metadata i32** %ptr0, metadata !969, metadata !107), !dbg !970
  %0 = load i32*, i32** %son.addr, align 8, !dbg !971
  %1 = load i32, i32* %cyclic_pos.addr, align 4, !dbg !972
  %shl = shl i32 %1, 1, !dbg !973
  %idx.ext = zext i32 %shl to i64, !dbg !974
  %add.ptr = getelementptr inbounds i32, i32* %0, i64 %idx.ext, !dbg !974
  %add.ptr1 = getelementptr inbounds i32, i32* %add.ptr, i64 1, !dbg !975
  store i32* %add.ptr1, i32** %ptr0, align 8, !dbg !970
  call void @llvm.dbg.declare(metadata i32** %ptr1, metadata !976, metadata !107), !dbg !977
  %2 = load i32*, i32** %son.addr, align 8, !dbg !978
  %3 = load i32, i32* %cyclic_pos.addr, align 4, !dbg !979
  %shl2 = shl i32 %3, 1, !dbg !980
  %idx.ext3 = zext i32 %shl2 to i64, !dbg !981
  %add.ptr4 = getelementptr inbounds i32, i32* %2, i64 %idx.ext3, !dbg !981
  store i32* %add.ptr4, i32** %ptr1, align 8, !dbg !977
  call void @llvm.dbg.declare(metadata i32* %len0, metadata !982, metadata !107), !dbg !983
  store i32 0, i32* %len0, align 4, !dbg !983
  call void @llvm.dbg.declare(metadata i32* %len1, metadata !984, metadata !107), !dbg !985
  store i32 0, i32* %len1, align 4, !dbg !985
  br label %while.body, !dbg !986

while.body:                                       ; preds = %entry, %if.end61
  call void @llvm.dbg.declare(metadata i32** %pair, metadata !987, metadata !107), !dbg !989
  call void @llvm.dbg.declare(metadata i8** %pb, metadata !990, metadata !107), !dbg !991
  call void @llvm.dbg.declare(metadata i32* %len, metadata !992, metadata !107), !dbg !993
  call void @llvm.dbg.declare(metadata i32* %delta, metadata !994, metadata !107), !dbg !995
  %4 = load i32, i32* %pos.addr, align 4, !dbg !996
  %5 = load i32, i32* %cur_match.addr, align 4, !dbg !997
  %sub = sub i32 %4, %5, !dbg !998
  store i32 %sub, i32* %delta, align 4, !dbg !995
  %6 = load i32, i32* %depth.addr, align 4, !dbg !999
  %dec = add i32 %6, -1, !dbg !999
  store i32 %dec, i32* %depth.addr, align 4, !dbg !999
  %cmp = icmp eq i32 %6, 0, !dbg !1001
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1002

lor.lhs.false:                                    ; preds = %while.body
  %7 = load i32, i32* %delta, align 4, !dbg !1003
  %8 = load i32, i32* %cyclic_size.addr, align 4, !dbg !1005
  %cmp5 = icmp uge i32 %7, %8, !dbg !1006
  br i1 %cmp5, label %if.then, label %if.end, !dbg !1007

if.then:                                          ; preds = %lor.lhs.false, %while.body
  %9 = load i32*, i32** %ptr0, align 8, !dbg !1008
  store i32 0, i32* %9, align 4, !dbg !1010
  %10 = load i32*, i32** %ptr1, align 8, !dbg !1011
  store i32 0, i32* %10, align 4, !dbg !1012
  %11 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1013
  store %struct.lzma_match* %11, %struct.lzma_match** %retval, align 8, !dbg !1014
  br label %return, !dbg !1014

if.end:                                           ; preds = %lor.lhs.false
  %12 = load i32*, i32** %son.addr, align 8, !dbg !1015
  %13 = load i32, i32* %cyclic_pos.addr, align 4, !dbg !1016
  %14 = load i32, i32* %delta, align 4, !dbg !1017
  %sub6 = sub i32 %13, %14, !dbg !1018
  %15 = load i32, i32* %delta, align 4, !dbg !1019
  %16 = load i32, i32* %cyclic_pos.addr, align 4, !dbg !1020
  %cmp7 = icmp ugt i32 %15, %16, !dbg !1021
  br i1 %cmp7, label %cond.true, label %cond.false, !dbg !1019

cond.true:                                        ; preds = %if.end
  %17 = load i32, i32* %cyclic_size.addr, align 4, !dbg !1022
  br label %cond.end, !dbg !1024

cond.false:                                       ; preds = %if.end
  br label %cond.end, !dbg !1025

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %17, %cond.true ], [ 0, %cond.false ], !dbg !1027
  %add = add i32 %sub6, %cond, !dbg !1029
  %shl8 = shl i32 %add, 1, !dbg !1030
  %idx.ext9 = zext i32 %shl8 to i64, !dbg !1031
  %add.ptr10 = getelementptr inbounds i32, i32* %12, i64 %idx.ext9, !dbg !1031
  store i32* %add.ptr10, i32** %pair, align 8, !dbg !1032
  %18 = load i8*, i8** %cur.addr, align 8, !dbg !1033
  %19 = load i32, i32* %delta, align 4, !dbg !1034
  %idx.ext11 = zext i32 %19 to i64, !dbg !1035
  %idx.neg = sub i64 0, %idx.ext11, !dbg !1035
  %add.ptr12 = getelementptr inbounds i8, i8* %18, i64 %idx.neg, !dbg !1035
  store i8* %add.ptr12, i8** %pb, align 8, !dbg !1036
  %20 = load i32, i32* %len0, align 4, !dbg !1037
  %21 = load i32, i32* %len1, align 4, !dbg !1037
  %cmp13 = icmp ult i32 %20, %21, !dbg !1037
  br i1 %cmp13, label %cond.true14, label %cond.false15, !dbg !1037

cond.true14:                                      ; preds = %cond.end
  %22 = load i32, i32* %len0, align 4, !dbg !1038
  br label %cond.end16, !dbg !1038

cond.false15:                                     ; preds = %cond.end
  %23 = load i32, i32* %len1, align 4, !dbg !1039
  br label %cond.end16, !dbg !1039

cond.end16:                                       ; preds = %cond.false15, %cond.true14
  %cond17 = phi i32 [ %22, %cond.true14 ], [ %23, %cond.false15 ], !dbg !1040
  store i32 %cond17, i32* %len, align 4, !dbg !1041
  %24 = load i32, i32* %len, align 4, !dbg !1042
  %idxprom = zext i32 %24 to i64, !dbg !1044
  %25 = load i8*, i8** %pb, align 8, !dbg !1044
  %arrayidx = getelementptr inbounds i8, i8* %25, i64 %idxprom, !dbg !1044
  %26 = load i8, i8* %arrayidx, align 1, !dbg !1044
  %conv = zext i8 %26 to i32, !dbg !1044
  %27 = load i32, i32* %len, align 4, !dbg !1045
  %idxprom18 = zext i32 %27 to i64, !dbg !1046
  %28 = load i8*, i8** %cur.addr, align 8, !dbg !1046
  %arrayidx19 = getelementptr inbounds i8, i8* %28, i64 %idxprom18, !dbg !1046
  %29 = load i8, i8* %arrayidx19, align 1, !dbg !1046
  %conv20 = zext i8 %29 to i32, !dbg !1046
  %cmp21 = icmp eq i32 %conv, %conv20, !dbg !1047
  br i1 %cmp21, label %if.then23, label %if.end50, !dbg !1048

if.then23:                                        ; preds = %cond.end16
  br label %while.cond24, !dbg !1049

while.cond24:                                     ; preds = %if.end37, %if.then23
  %30 = load i32, i32* %len, align 4, !dbg !1051
  %inc = add i32 %30, 1, !dbg !1051
  store i32 %inc, i32* %len, align 4, !dbg !1051
  %31 = load i32, i32* %len_limit.addr, align 4, !dbg !1053
  %cmp25 = icmp ne i32 %inc, %31, !dbg !1054
  br i1 %cmp25, label %while.body27, label %while.end, !dbg !1055

while.body27:                                     ; preds = %while.cond24
  %32 = load i32, i32* %len, align 4, !dbg !1056
  %idxprom28 = zext i32 %32 to i64, !dbg !1058
  %33 = load i8*, i8** %pb, align 8, !dbg !1058
  %arrayidx29 = getelementptr inbounds i8, i8* %33, i64 %idxprom28, !dbg !1058
  %34 = load i8, i8* %arrayidx29, align 1, !dbg !1058
  %conv30 = zext i8 %34 to i32, !dbg !1058
  %35 = load i32, i32* %len, align 4, !dbg !1059
  %idxprom31 = zext i32 %35 to i64, !dbg !1060
  %36 = load i8*, i8** %cur.addr, align 8, !dbg !1060
  %arrayidx32 = getelementptr inbounds i8, i8* %36, i64 %idxprom31, !dbg !1060
  %37 = load i8, i8* %arrayidx32, align 1, !dbg !1060
  %conv33 = zext i8 %37 to i32, !dbg !1060
  %cmp34 = icmp ne i32 %conv30, %conv33, !dbg !1061
  br i1 %cmp34, label %if.then36, label %if.end37, !dbg !1062

if.then36:                                        ; preds = %while.body27
  br label %while.end, !dbg !1063

if.end37:                                         ; preds = %while.body27
  br label %while.cond24, !dbg !1064

while.end:                                        ; preds = %if.then36, %while.cond24
  %38 = load i32, i32* %len_best.addr, align 4, !dbg !1066
  %39 = load i32, i32* %len, align 4, !dbg !1068
  %cmp38 = icmp ult i32 %38, %39, !dbg !1069
  br i1 %cmp38, label %if.then40, label %if.end49, !dbg !1070

if.then40:                                        ; preds = %while.end
  %40 = load i32, i32* %len, align 4, !dbg !1071
  store i32 %40, i32* %len_best.addr, align 4, !dbg !1073
  %41 = load i32, i32* %len, align 4, !dbg !1074
  %42 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1075
  %len41 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %42, i32 0, i32 0, !dbg !1076
  store i32 %41, i32* %len41, align 4, !dbg !1077
  %43 = load i32, i32* %delta, align 4, !dbg !1078
  %sub42 = sub i32 %43, 1, !dbg !1079
  %44 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1080
  %dist = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %44, i32 0, i32 1, !dbg !1081
  store i32 %sub42, i32* %dist, align 4, !dbg !1082
  %45 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1083
  %incdec.ptr = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %45, i32 1, !dbg !1083
  store %struct.lzma_match* %incdec.ptr, %struct.lzma_match** %matches.addr, align 8, !dbg !1083
  %46 = load i32, i32* %len, align 4, !dbg !1084
  %47 = load i32, i32* %len_limit.addr, align 4, !dbg !1086
  %cmp43 = icmp eq i32 %46, %47, !dbg !1087
  br i1 %cmp43, label %if.then45, label %if.end48, !dbg !1088

if.then45:                                        ; preds = %if.then40
  %48 = load i32*, i32** %pair, align 8, !dbg !1089
  %arrayidx46 = getelementptr inbounds i32, i32* %48, i64 0, !dbg !1089
  %49 = load i32, i32* %arrayidx46, align 4, !dbg !1089
  %50 = load i32*, i32** %ptr1, align 8, !dbg !1091
  store i32 %49, i32* %50, align 4, !dbg !1092
  %51 = load i32*, i32** %pair, align 8, !dbg !1093
  %arrayidx47 = getelementptr inbounds i32, i32* %51, i64 1, !dbg !1093
  %52 = load i32, i32* %arrayidx47, align 4, !dbg !1093
  %53 = load i32*, i32** %ptr0, align 8, !dbg !1094
  store i32 %52, i32* %53, align 4, !dbg !1095
  %54 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1096
  store %struct.lzma_match* %54, %struct.lzma_match** %retval, align 8, !dbg !1097
  br label %return, !dbg !1097

if.end48:                                         ; preds = %if.then40
  br label %if.end49, !dbg !1098

if.end49:                                         ; preds = %if.end48, %while.end
  br label %if.end50, !dbg !1099

if.end50:                                         ; preds = %if.end49, %cond.end16
  %55 = load i32, i32* %len, align 4, !dbg !1100
  %idxprom51 = zext i32 %55 to i64, !dbg !1102
  %56 = load i8*, i8** %pb, align 8, !dbg !1102
  %arrayidx52 = getelementptr inbounds i8, i8* %56, i64 %idxprom51, !dbg !1102
  %57 = load i8, i8* %arrayidx52, align 1, !dbg !1102
  %conv53 = zext i8 %57 to i32, !dbg !1102
  %58 = load i32, i32* %len, align 4, !dbg !1103
  %idxprom54 = zext i32 %58 to i64, !dbg !1104
  %59 = load i8*, i8** %cur.addr, align 8, !dbg !1104
  %arrayidx55 = getelementptr inbounds i8, i8* %59, i64 %idxprom54, !dbg !1104
  %60 = load i8, i8* %arrayidx55, align 1, !dbg !1104
  %conv56 = zext i8 %60 to i32, !dbg !1104
  %cmp57 = icmp slt i32 %conv53, %conv56, !dbg !1105
  br i1 %cmp57, label %if.then59, label %if.else, !dbg !1106

if.then59:                                        ; preds = %if.end50
  %61 = load i32, i32* %cur_match.addr, align 4, !dbg !1107
  %62 = load i32*, i32** %ptr1, align 8, !dbg !1109
  store i32 %61, i32* %62, align 4, !dbg !1110
  %63 = load i32*, i32** %pair, align 8, !dbg !1111
  %add.ptr60 = getelementptr inbounds i32, i32* %63, i64 1, !dbg !1112
  store i32* %add.ptr60, i32** %ptr1, align 8, !dbg !1113
  %64 = load i32*, i32** %ptr1, align 8, !dbg !1114
  %65 = load i32, i32* %64, align 4, !dbg !1115
  store i32 %65, i32* %cur_match.addr, align 4, !dbg !1116
  %66 = load i32, i32* %len, align 4, !dbg !1117
  store i32 %66, i32* %len1, align 4, !dbg !1118
  br label %if.end61, !dbg !1119

if.else:                                          ; preds = %if.end50
  %67 = load i32, i32* %cur_match.addr, align 4, !dbg !1120
  %68 = load i32*, i32** %ptr0, align 8, !dbg !1122
  store i32 %67, i32* %68, align 4, !dbg !1123
  %69 = load i32*, i32** %pair, align 8, !dbg !1124
  store i32* %69, i32** %ptr0, align 8, !dbg !1125
  %70 = load i32*, i32** %ptr0, align 8, !dbg !1126
  %71 = load i32, i32* %70, align 4, !dbg !1127
  store i32 %71, i32* %cur_match.addr, align 4, !dbg !1128
  %72 = load i32, i32* %len, align 4, !dbg !1129
  store i32 %72, i32* %len0, align 4, !dbg !1130
  br label %if.end61

if.end61:                                         ; preds = %if.else, %if.then59
  br label %while.body, !dbg !1131

return:                                           ; preds = %if.then45, %if.then
  %73 = load %struct.lzma_match*, %struct.lzma_match** %retval, align 8, !dbg !1133
  ret %struct.lzma_match* %73, !dbg !1133
}

; Function Attrs: nounwind uwtable
define void @lzma_mf_bt2_skip(%struct.lzma_mf_s* %mf, i32 %amount) #0 !dbg !73 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %amount.addr = alloca i32, align 4
  %cur = alloca i8*, align 8
  %pos = alloca i32, align 4
  %hash_value = alloca i32, align 4
  %cur_match = alloca i32, align 4
  %len_limit = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !1134, metadata !107), !dbg !1135
  store i32 %amount, i32* %amount.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %amount.addr, metadata !1136, metadata !107), !dbg !1137
  br label %do.body, !dbg !1138

do.body:                                          ; preds = %do.cond, %entry
  call void @llvm.dbg.declare(metadata i8** %cur, metadata !1139, metadata !107), !dbg !1141
  call void @llvm.dbg.declare(metadata i32* %pos, metadata !1142, metadata !107), !dbg !1143
  call void @llvm.dbg.declare(metadata i32* %hash_value, metadata !1144, metadata !107), !dbg !1145
  call void @llvm.dbg.declare(metadata i32* %cur_match, metadata !1146, metadata !107), !dbg !1147
  call void @llvm.dbg.declare(metadata i32* %len_limit, metadata !1148, metadata !107), !dbg !1149
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1149
  %call = call i32 @mf_avail(%struct.lzma_mf_s* %0), !dbg !1149
  store i32 %call, i32* %len_limit, align 4, !dbg !1149
  %1 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1150
  %nice_len = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %1, i32 0, i32 18, !dbg !1150
  %2 = load i32, i32* %nice_len, align 8, !dbg !1150
  %3 = load i32, i32* %len_limit, align 4, !dbg !1150
  %cmp = icmp ule i32 %2, %3, !dbg !1150
  br i1 %cmp, label %if.then, label %if.else, !dbg !1149

if.then:                                          ; preds = %do.body
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1152
  %nice_len1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %4, i32 0, i32 18, !dbg !1152
  %5 = load i32, i32* %nice_len1, align 8, !dbg !1152
  store i32 %5, i32* %len_limit, align 4, !dbg !1152
  br label %if.end7, !dbg !1152

if.else:                                          ; preds = %do.body
  %6 = load i32, i32* %len_limit, align 4, !dbg !1155
  %cmp2 = icmp ult i32 %6, 2, !dbg !1155
  br i1 %cmp2, label %if.then4, label %lor.lhs.false, !dbg !1155

lor.lhs.false:                                    ; preds = %if.else
  %7 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1158
  %action = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %7, i32 0, i32 20, !dbg !1158
  %8 = load i32, i32* %action, align 8, !dbg !1158
  %cmp3 = icmp eq i32 %8, 1, !dbg !1158
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !1158

if.then4:                                         ; preds = %lor.lhs.false, %if.else
  %9 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1160
  %action5 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %9, i32 0, i32 20, !dbg !1160
  %10 = load i32, i32* %action5, align 8, !dbg !1160
  %cmp6 = icmp ne i32 %10, 0, !dbg !1160
  br i1 %cmp6, label %cond.true, label %cond.false, !dbg !1160

cond.true:                                        ; preds = %if.then4
  br label %cond.end, !dbg !1163

cond.false:                                       ; preds = %if.then4
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.1, i32 0, i32 0), i32 655, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @__PRETTY_FUNCTION__.lzma_mf_bt2_skip, i32 0, i32 0)) #5, !dbg !1165
  unreachable, !dbg !1165
                                                  ; No predecessors!
  br label %cond.end, !dbg !1167

cond.end:                                         ; preds = %11, %cond.true
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1169
  call void @move_pending(%struct.lzma_mf_s* %12), !dbg !1169
  br label %do.cond, !dbg !1169

if.end:                                           ; preds = %lor.lhs.false
  br label %if.end7

if.end7:                                          ; preds = %if.end, %if.then
  %13 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1171
  %call8 = call i8* @mf_ptr(%struct.lzma_mf_s* %13), !dbg !1171
  store i8* %call8, i8** %cur, align 8, !dbg !1171
  %14 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1171
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %14, i32 0, i32 5, !dbg !1171
  %15 = load i32, i32* %read_pos, align 8, !dbg !1171
  %16 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1171
  %offset = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %16, i32 0, i32 4, !dbg !1171
  %17 = load i32, i32* %offset, align 4, !dbg !1171
  %add = add i32 %15, %17, !dbg !1171
  store i32 %add, i32* %pos, align 4, !dbg !1171
  %18 = load i8*, i8** %cur, align 8, !dbg !1173
  %19 = bitcast i8* %18 to i16*, !dbg !1173
  %20 = load i16, i16* %19, align 2, !dbg !1173
  %conv = zext i16 %20 to i32, !dbg !1173
  store i32 %conv, i32* %hash_value, align 4, !dbg !1173
  %21 = load i32, i32* %hash_value, align 4, !dbg !1174
  %idxprom = zext i32 %21 to i64, !dbg !1175
  %22 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1175
  %hash = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %22, i32 0, i32 12, !dbg !1176
  %23 = load i32*, i32** %hash, align 8, !dbg !1176
  %arrayidx = getelementptr inbounds i32, i32* %23, i64 %idxprom, !dbg !1175
  %24 = load i32, i32* %arrayidx, align 4, !dbg !1175
  store i32 %24, i32* %cur_match, align 4, !dbg !1177
  %25 = load i32, i32* %pos, align 4, !dbg !1178
  %26 = load i32, i32* %hash_value, align 4, !dbg !1179
  %idxprom9 = zext i32 %26 to i64, !dbg !1180
  %27 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1180
  %hash10 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %27, i32 0, i32 12, !dbg !1181
  %28 = load i32*, i32** %hash10, align 8, !dbg !1181
  %arrayidx11 = getelementptr inbounds i32, i32* %28, i64 %idxprom9, !dbg !1180
  store i32 %25, i32* %arrayidx11, align 4, !dbg !1182
  br label %do.body12, !dbg !1183

do.body12:                                        ; preds = %if.end7
  %29 = load i32, i32* %len_limit, align 4, !dbg !1184
  %30 = load i32, i32* %pos, align 4, !dbg !1184
  %31 = load i8*, i8** %cur, align 8, !dbg !1184
  %32 = load i32, i32* %cur_match, align 4, !dbg !1184
  %33 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1184
  %depth = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %33, i32 0, i32 17, !dbg !1184
  %34 = load i32, i32* %depth, align 4, !dbg !1184
  %35 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1184
  %son = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %35, i32 0, i32 13, !dbg !1184
  %36 = load i32*, i32** %son, align 8, !dbg !1184
  %37 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1184
  %cyclic_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %37, i32 0, i32 14, !dbg !1184
  %38 = load i32, i32* %cyclic_pos, align 8, !dbg !1184
  %39 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1184
  %cyclic_size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %39, i32 0, i32 15, !dbg !1184
  %40 = load i32, i32* %cyclic_size, align 4, !dbg !1184
  call void @bt_skip_func(i32 %29, i32 %30, i8* %31, i32 %32, i32 %34, i32* %36, i32 %38, i32 %40), !dbg !1184
  %41 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1184
  call void @move_pos(%struct.lzma_mf_s* %41), !dbg !1187
  br label %do.end, !dbg !1184

do.end:                                           ; preds = %do.body12
  br label %do.cond, !dbg !1189

do.cond:                                          ; preds = %do.end, %cond.end
  %42 = load i32, i32* %amount.addr, align 4, !dbg !1190
  %dec = add i32 %42, -1, !dbg !1190
  store i32 %dec, i32* %amount.addr, align 4, !dbg !1190
  %cmp13 = icmp ne i32 %dec, 0, !dbg !1192
  br i1 %cmp13, label %do.body, label %do.end15, !dbg !1193

do.end15:                                         ; preds = %do.cond
  ret void, !dbg !1194
}

; Function Attrs: nounwind uwtable
define internal void @bt_skip_func(i32 %len_limit, i32 %pos, i8* %cur, i32 %cur_match, i32 %depth, i32* %son, i32 %cyclic_pos, i32 %cyclic_size) #0 !dbg !100 {
entry:
  %len_limit.addr = alloca i32, align 4
  %pos.addr = alloca i32, align 4
  %cur.addr = alloca i8*, align 8
  %cur_match.addr = alloca i32, align 4
  %depth.addr = alloca i32, align 4
  %son.addr = alloca i32*, align 8
  %cyclic_pos.addr = alloca i32, align 4
  %cyclic_size.addr = alloca i32, align 4
  %ptr0 = alloca i32*, align 8
  %ptr1 = alloca i32*, align 8
  %len0 = alloca i32, align 4
  %len1 = alloca i32, align 4
  %pair = alloca i32*, align 8
  %pb = alloca i8*, align 8
  %len = alloca i32, align 4
  %delta = alloca i32, align 4
  store i32 %len_limit, i32* %len_limit.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len_limit.addr, metadata !1195, metadata !107), !dbg !1196
  store i32 %pos, i32* %pos.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos.addr, metadata !1197, metadata !107), !dbg !1198
  store i8* %cur, i8** %cur.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cur.addr, metadata !1199, metadata !107), !dbg !1200
  store i32 %cur_match, i32* %cur_match.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %cur_match.addr, metadata !1201, metadata !107), !dbg !1202
  store i32 %depth, i32* %depth.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %depth.addr, metadata !1203, metadata !107), !dbg !1204
  store i32* %son, i32** %son.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %son.addr, metadata !1205, metadata !107), !dbg !1206
  store i32 %cyclic_pos, i32* %cyclic_pos.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %cyclic_pos.addr, metadata !1207, metadata !107), !dbg !1208
  store i32 %cyclic_size, i32* %cyclic_size.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %cyclic_size.addr, metadata !1209, metadata !107), !dbg !1210
  call void @llvm.dbg.declare(metadata i32** %ptr0, metadata !1211, metadata !107), !dbg !1212
  %0 = load i32*, i32** %son.addr, align 8, !dbg !1213
  %1 = load i32, i32* %cyclic_pos.addr, align 4, !dbg !1214
  %shl = shl i32 %1, 1, !dbg !1215
  %idx.ext = zext i32 %shl to i64, !dbg !1216
  %add.ptr = getelementptr inbounds i32, i32* %0, i64 %idx.ext, !dbg !1216
  %add.ptr1 = getelementptr inbounds i32, i32* %add.ptr, i64 1, !dbg !1217
  store i32* %add.ptr1, i32** %ptr0, align 8, !dbg !1212
  call void @llvm.dbg.declare(metadata i32** %ptr1, metadata !1218, metadata !107), !dbg !1219
  %2 = load i32*, i32** %son.addr, align 8, !dbg !1220
  %3 = load i32, i32* %cyclic_pos.addr, align 4, !dbg !1221
  %shl2 = shl i32 %3, 1, !dbg !1222
  %idx.ext3 = zext i32 %shl2 to i64, !dbg !1223
  %add.ptr4 = getelementptr inbounds i32, i32* %2, i64 %idx.ext3, !dbg !1223
  store i32* %add.ptr4, i32** %ptr1, align 8, !dbg !1219
  call void @llvm.dbg.declare(metadata i32* %len0, metadata !1224, metadata !107), !dbg !1225
  store i32 0, i32* %len0, align 4, !dbg !1225
  call void @llvm.dbg.declare(metadata i32* %len1, metadata !1226, metadata !107), !dbg !1227
  store i32 0, i32* %len1, align 4, !dbg !1227
  br label %while.body, !dbg !1228

while.body:                                       ; preds = %entry, %if.end55
  call void @llvm.dbg.declare(metadata i32** %pair, metadata !1229, metadata !107), !dbg !1231
  call void @llvm.dbg.declare(metadata i8** %pb, metadata !1232, metadata !107), !dbg !1233
  call void @llvm.dbg.declare(metadata i32* %len, metadata !1234, metadata !107), !dbg !1235
  call void @llvm.dbg.declare(metadata i32* %delta, metadata !1236, metadata !107), !dbg !1237
  %4 = load i32, i32* %pos.addr, align 4, !dbg !1238
  %5 = load i32, i32* %cur_match.addr, align 4, !dbg !1239
  %sub = sub i32 %4, %5, !dbg !1240
  store i32 %sub, i32* %delta, align 4, !dbg !1237
  %6 = load i32, i32* %depth.addr, align 4, !dbg !1241
  %dec = add i32 %6, -1, !dbg !1241
  store i32 %dec, i32* %depth.addr, align 4, !dbg !1241
  %cmp = icmp eq i32 %6, 0, !dbg !1243
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1244

lor.lhs.false:                                    ; preds = %while.body
  %7 = load i32, i32* %delta, align 4, !dbg !1245
  %8 = load i32, i32* %cyclic_size.addr, align 4, !dbg !1247
  %cmp5 = icmp uge i32 %7, %8, !dbg !1248
  br i1 %cmp5, label %if.then, label %if.end, !dbg !1249

if.then:                                          ; preds = %lor.lhs.false, %while.body
  %9 = load i32*, i32** %ptr0, align 8, !dbg !1250
  store i32 0, i32* %9, align 4, !dbg !1252
  %10 = load i32*, i32** %ptr1, align 8, !dbg !1253
  store i32 0, i32* %10, align 4, !dbg !1254
  br label %return, !dbg !1255

if.end:                                           ; preds = %lor.lhs.false
  %11 = load i32*, i32** %son.addr, align 8, !dbg !1256
  %12 = load i32, i32* %cyclic_pos.addr, align 4, !dbg !1257
  %13 = load i32, i32* %delta, align 4, !dbg !1258
  %sub6 = sub i32 %12, %13, !dbg !1259
  %14 = load i32, i32* %delta, align 4, !dbg !1260
  %15 = load i32, i32* %cyclic_pos.addr, align 4, !dbg !1261
  %cmp7 = icmp ugt i32 %14, %15, !dbg !1262
  br i1 %cmp7, label %cond.true, label %cond.false, !dbg !1260

cond.true:                                        ; preds = %if.end
  %16 = load i32, i32* %cyclic_size.addr, align 4, !dbg !1263
  br label %cond.end, !dbg !1265

cond.false:                                       ; preds = %if.end
  br label %cond.end, !dbg !1266

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %16, %cond.true ], [ 0, %cond.false ], !dbg !1268
  %add = add i32 %sub6, %cond, !dbg !1270
  %shl8 = shl i32 %add, 1, !dbg !1271
  %idx.ext9 = zext i32 %shl8 to i64, !dbg !1272
  %add.ptr10 = getelementptr inbounds i32, i32* %11, i64 %idx.ext9, !dbg !1272
  store i32* %add.ptr10, i32** %pair, align 8, !dbg !1273
  %17 = load i8*, i8** %cur.addr, align 8, !dbg !1274
  %18 = load i32, i32* %delta, align 4, !dbg !1275
  %idx.ext11 = zext i32 %18 to i64, !dbg !1276
  %idx.neg = sub i64 0, %idx.ext11, !dbg !1276
  %add.ptr12 = getelementptr inbounds i8, i8* %17, i64 %idx.neg, !dbg !1276
  store i8* %add.ptr12, i8** %pb, align 8, !dbg !1277
  %19 = load i32, i32* %len0, align 4, !dbg !1278
  %20 = load i32, i32* %len1, align 4, !dbg !1278
  %cmp13 = icmp ult i32 %19, %20, !dbg !1278
  br i1 %cmp13, label %cond.true14, label %cond.false15, !dbg !1278

cond.true14:                                      ; preds = %cond.end
  %21 = load i32, i32* %len0, align 4, !dbg !1279
  br label %cond.end16, !dbg !1279

cond.false15:                                     ; preds = %cond.end
  %22 = load i32, i32* %len1, align 4, !dbg !1280
  br label %cond.end16, !dbg !1280

cond.end16:                                       ; preds = %cond.false15, %cond.true14
  %cond17 = phi i32 [ %21, %cond.true14 ], [ %22, %cond.false15 ], !dbg !1281
  store i32 %cond17, i32* %len, align 4, !dbg !1282
  %23 = load i32, i32* %len, align 4, !dbg !1283
  %idxprom = zext i32 %23 to i64, !dbg !1285
  %24 = load i8*, i8** %pb, align 8, !dbg !1285
  %arrayidx = getelementptr inbounds i8, i8* %24, i64 %idxprom, !dbg !1285
  %25 = load i8, i8* %arrayidx, align 1, !dbg !1285
  %conv = zext i8 %25 to i32, !dbg !1285
  %26 = load i32, i32* %len, align 4, !dbg !1286
  %idxprom18 = zext i32 %26 to i64, !dbg !1287
  %27 = load i8*, i8** %cur.addr, align 8, !dbg !1287
  %arrayidx19 = getelementptr inbounds i8, i8* %27, i64 %idxprom18, !dbg !1287
  %28 = load i8, i8* %arrayidx19, align 1, !dbg !1287
  %conv20 = zext i8 %28 to i32, !dbg !1287
  %cmp21 = icmp eq i32 %conv, %conv20, !dbg !1288
  br i1 %cmp21, label %if.then23, label %if.end44, !dbg !1289

if.then23:                                        ; preds = %cond.end16
  br label %while.cond24, !dbg !1290

while.cond24:                                     ; preds = %if.end37, %if.then23
  %29 = load i32, i32* %len, align 4, !dbg !1292
  %inc = add i32 %29, 1, !dbg !1292
  store i32 %inc, i32* %len, align 4, !dbg !1292
  %30 = load i32, i32* %len_limit.addr, align 4, !dbg !1294
  %cmp25 = icmp ne i32 %inc, %30, !dbg !1295
  br i1 %cmp25, label %while.body27, label %while.end, !dbg !1296

while.body27:                                     ; preds = %while.cond24
  %31 = load i32, i32* %len, align 4, !dbg !1297
  %idxprom28 = zext i32 %31 to i64, !dbg !1299
  %32 = load i8*, i8** %pb, align 8, !dbg !1299
  %arrayidx29 = getelementptr inbounds i8, i8* %32, i64 %idxprom28, !dbg !1299
  %33 = load i8, i8* %arrayidx29, align 1, !dbg !1299
  %conv30 = zext i8 %33 to i32, !dbg !1299
  %34 = load i32, i32* %len, align 4, !dbg !1300
  %idxprom31 = zext i32 %34 to i64, !dbg !1301
  %35 = load i8*, i8** %cur.addr, align 8, !dbg !1301
  %arrayidx32 = getelementptr inbounds i8, i8* %35, i64 %idxprom31, !dbg !1301
  %36 = load i8, i8* %arrayidx32, align 1, !dbg !1301
  %conv33 = zext i8 %36 to i32, !dbg !1301
  %cmp34 = icmp ne i32 %conv30, %conv33, !dbg !1302
  br i1 %cmp34, label %if.then36, label %if.end37, !dbg !1303

if.then36:                                        ; preds = %while.body27
  br label %while.end, !dbg !1304

if.end37:                                         ; preds = %while.body27
  br label %while.cond24, !dbg !1305

while.end:                                        ; preds = %if.then36, %while.cond24
  %37 = load i32, i32* %len, align 4, !dbg !1307
  %38 = load i32, i32* %len_limit.addr, align 4, !dbg !1309
  %cmp38 = icmp eq i32 %37, %38, !dbg !1310
  br i1 %cmp38, label %if.then40, label %if.end43, !dbg !1311

if.then40:                                        ; preds = %while.end
  %39 = load i32*, i32** %pair, align 8, !dbg !1312
  %arrayidx41 = getelementptr inbounds i32, i32* %39, i64 0, !dbg !1312
  %40 = load i32, i32* %arrayidx41, align 4, !dbg !1312
  %41 = load i32*, i32** %ptr1, align 8, !dbg !1314
  store i32 %40, i32* %41, align 4, !dbg !1315
  %42 = load i32*, i32** %pair, align 8, !dbg !1316
  %arrayidx42 = getelementptr inbounds i32, i32* %42, i64 1, !dbg !1316
  %43 = load i32, i32* %arrayidx42, align 4, !dbg !1316
  %44 = load i32*, i32** %ptr0, align 8, !dbg !1317
  store i32 %43, i32* %44, align 4, !dbg !1318
  br label %return, !dbg !1319

if.end43:                                         ; preds = %while.end
  br label %if.end44, !dbg !1320

if.end44:                                         ; preds = %if.end43, %cond.end16
  %45 = load i32, i32* %len, align 4, !dbg !1321
  %idxprom45 = zext i32 %45 to i64, !dbg !1323
  %46 = load i8*, i8** %pb, align 8, !dbg !1323
  %arrayidx46 = getelementptr inbounds i8, i8* %46, i64 %idxprom45, !dbg !1323
  %47 = load i8, i8* %arrayidx46, align 1, !dbg !1323
  %conv47 = zext i8 %47 to i32, !dbg !1323
  %48 = load i32, i32* %len, align 4, !dbg !1324
  %idxprom48 = zext i32 %48 to i64, !dbg !1325
  %49 = load i8*, i8** %cur.addr, align 8, !dbg !1325
  %arrayidx49 = getelementptr inbounds i8, i8* %49, i64 %idxprom48, !dbg !1325
  %50 = load i8, i8* %arrayidx49, align 1, !dbg !1325
  %conv50 = zext i8 %50 to i32, !dbg !1325
  %cmp51 = icmp slt i32 %conv47, %conv50, !dbg !1326
  br i1 %cmp51, label %if.then53, label %if.else, !dbg !1327

if.then53:                                        ; preds = %if.end44
  %51 = load i32, i32* %cur_match.addr, align 4, !dbg !1328
  %52 = load i32*, i32** %ptr1, align 8, !dbg !1330
  store i32 %51, i32* %52, align 4, !dbg !1331
  %53 = load i32*, i32** %pair, align 8, !dbg !1332
  %add.ptr54 = getelementptr inbounds i32, i32* %53, i64 1, !dbg !1333
  store i32* %add.ptr54, i32** %ptr1, align 8, !dbg !1334
  %54 = load i32*, i32** %ptr1, align 8, !dbg !1335
  %55 = load i32, i32* %54, align 4, !dbg !1336
  store i32 %55, i32* %cur_match.addr, align 4, !dbg !1337
  %56 = load i32, i32* %len, align 4, !dbg !1338
  store i32 %56, i32* %len1, align 4, !dbg !1339
  br label %if.end55, !dbg !1340

if.else:                                          ; preds = %if.end44
  %57 = load i32, i32* %cur_match.addr, align 4, !dbg !1341
  %58 = load i32*, i32** %ptr0, align 8, !dbg !1343
  store i32 %57, i32* %58, align 4, !dbg !1344
  %59 = load i32*, i32** %pair, align 8, !dbg !1345
  store i32* %59, i32** %ptr0, align 8, !dbg !1346
  %60 = load i32*, i32** %ptr0, align 8, !dbg !1347
  %61 = load i32, i32* %60, align 4, !dbg !1348
  store i32 %61, i32* %cur_match.addr, align 4, !dbg !1349
  %62 = load i32, i32* %len, align 4, !dbg !1350
  store i32 %62, i32* %len0, align 4, !dbg !1351
  br label %if.end55

if.end55:                                         ; preds = %if.else, %if.then53
  br label %while.body, !dbg !1352

return:                                           ; preds = %if.then40, %if.then
  ret void, !dbg !1354
}

; Function Attrs: nounwind uwtable
define i32 @lzma_mf_bt3_find(%struct.lzma_mf_s* %mf, %struct.lzma_match* %matches) #0 !dbg !74 {
entry:
  %retval = alloca i32, align 4
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %matches.addr = alloca %struct.lzma_match*, align 8
  %cur = alloca i8*, align 8
  %pos = alloca i32, align 4
  %temp = alloca i32, align 4
  %hash_value = alloca i32, align 4
  %hash_2_value = alloca i32, align 4
  %delta2 = alloca i32, align 4
  %cur_match = alloca i32, align 4
  %len_best = alloca i32, align 4
  %matches_count = alloca i32, align 4
  %len_limit = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !1355, metadata !107), !dbg !1356
  store %struct.lzma_match* %matches, %struct.lzma_match** %matches.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_match** %matches.addr, metadata !1357, metadata !107), !dbg !1358
  call void @llvm.dbg.declare(metadata i8** %cur, metadata !1359, metadata !107), !dbg !1360
  call void @llvm.dbg.declare(metadata i32* %pos, metadata !1361, metadata !107), !dbg !1362
  call void @llvm.dbg.declare(metadata i32* %temp, metadata !1363, metadata !107), !dbg !1364
  call void @llvm.dbg.declare(metadata i32* %hash_value, metadata !1365, metadata !107), !dbg !1366
  call void @llvm.dbg.declare(metadata i32* %hash_2_value, metadata !1367, metadata !107), !dbg !1368
  call void @llvm.dbg.declare(metadata i32* %delta2, metadata !1369, metadata !107), !dbg !1370
  call void @llvm.dbg.declare(metadata i32* %cur_match, metadata !1371, metadata !107), !dbg !1372
  call void @llvm.dbg.declare(metadata i32* %len_best, metadata !1373, metadata !107), !dbg !1374
  store i32 2, i32* %len_best, align 4, !dbg !1374
  call void @llvm.dbg.declare(metadata i32* %matches_count, metadata !1375, metadata !107), !dbg !1376
  store i32 0, i32* %matches_count, align 4, !dbg !1376
  call void @llvm.dbg.declare(metadata i32* %len_limit, metadata !1377, metadata !107), !dbg !1378
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1378
  %call = call i32 @mf_avail(%struct.lzma_mf_s* %0), !dbg !1378
  store i32 %call, i32* %len_limit, align 4, !dbg !1378
  %1 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1379
  %nice_len = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %1, i32 0, i32 18, !dbg !1379
  %2 = load i32, i32* %nice_len, align 8, !dbg !1379
  %3 = load i32, i32* %len_limit, align 4, !dbg !1379
  %cmp = icmp ule i32 %2, %3, !dbg !1379
  br i1 %cmp, label %if.then, label %if.else, !dbg !1378

if.then:                                          ; preds = %entry
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1381
  %nice_len1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %4, i32 0, i32 18, !dbg !1381
  %5 = load i32, i32* %nice_len1, align 8, !dbg !1381
  store i32 %5, i32* %len_limit, align 4, !dbg !1381
  br label %if.end7, !dbg !1381

if.else:                                          ; preds = %entry
  %6 = load i32, i32* %len_limit, align 4, !dbg !1384
  %cmp2 = icmp ult i32 %6, 3, !dbg !1384
  br i1 %cmp2, label %if.then4, label %lor.lhs.false, !dbg !1384

lor.lhs.false:                                    ; preds = %if.else
  %7 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1387
  %action = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %7, i32 0, i32 20, !dbg !1387
  %8 = load i32, i32* %action, align 8, !dbg !1387
  %cmp3 = icmp eq i32 %8, 1, !dbg !1387
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !1387

if.then4:                                         ; preds = %lor.lhs.false, %if.else
  %9 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1389
  %action5 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %9, i32 0, i32 20, !dbg !1389
  %10 = load i32, i32* %action5, align 8, !dbg !1389
  %cmp6 = icmp ne i32 %10, 0, !dbg !1389
  br i1 %cmp6, label %cond.true, label %cond.false, !dbg !1389

cond.true:                                        ; preds = %if.then4
  br label %cond.end, !dbg !1392

cond.false:                                       ; preds = %if.then4
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.1, i32 0, i32 0), i32 680, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @__PRETTY_FUNCTION__.lzma_mf_bt3_find, i32 0, i32 0)) #5, !dbg !1394
  unreachable, !dbg !1394
                                                  ; No predecessors!
  br label %cond.end, !dbg !1396

cond.end:                                         ; preds = %11, %cond.true
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1398
  call void @move_pending(%struct.lzma_mf_s* %12), !dbg !1398
  store i32 0, i32* %retval, align 4, !dbg !1398
  br label %do.end68, !dbg !1398

if.end:                                           ; preds = %lor.lhs.false
  br label %if.end7

if.end7:                                          ; preds = %if.end, %if.then
  %13 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1400
  %call8 = call i8* @mf_ptr(%struct.lzma_mf_s* %13), !dbg !1400
  store i8* %call8, i8** %cur, align 8, !dbg !1400
  %14 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1400
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %14, i32 0, i32 5, !dbg !1400
  %15 = load i32, i32* %read_pos, align 8, !dbg !1400
  %16 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1400
  %offset = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %16, i32 0, i32 4, !dbg !1400
  %17 = load i32, i32* %offset, align 4, !dbg !1400
  %add = add i32 %15, %17, !dbg !1400
  store i32 %add, i32* %pos, align 4, !dbg !1400
  %18 = load i8*, i8** %cur, align 8, !dbg !1402
  %arrayidx = getelementptr inbounds i8, i8* %18, i64 0, !dbg !1402
  %19 = load i8, i8* %arrayidx, align 1, !dbg !1402
  %idxprom = zext i8 %19 to i64, !dbg !1402
  %arrayidx9 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom, !dbg !1402
  %20 = load i32, i32* %arrayidx9, align 4, !dbg !1402
  %21 = load i8*, i8** %cur, align 8, !dbg !1402
  %arrayidx10 = getelementptr inbounds i8, i8* %21, i64 1, !dbg !1402
  %22 = load i8, i8* %arrayidx10, align 1, !dbg !1402
  %conv = zext i8 %22 to i32, !dbg !1402
  %xor = xor i32 %20, %conv, !dbg !1402
  store i32 %xor, i32* %temp, align 4, !dbg !1402
  %23 = load i32, i32* %temp, align 4, !dbg !1402
  %and = and i32 %23, 1023, !dbg !1402
  store i32 %and, i32* %hash_2_value, align 4, !dbg !1402
  %24 = load i32, i32* %temp, align 4, !dbg !1402
  %25 = load i8*, i8** %cur, align 8, !dbg !1402
  %arrayidx11 = getelementptr inbounds i8, i8* %25, i64 2, !dbg !1402
  %26 = load i8, i8* %arrayidx11, align 1, !dbg !1402
  %conv12 = zext i8 %26 to i32, !dbg !1402
  %shl = shl i32 %conv12, 8, !dbg !1402
  %xor13 = xor i32 %24, %shl, !dbg !1402
  %27 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1402
  %hash_mask = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %27, i32 0, i32 16, !dbg !1402
  %28 = load i32, i32* %hash_mask, align 8, !dbg !1402
  %and14 = and i32 %xor13, %28, !dbg !1402
  store i32 %and14, i32* %hash_value, align 4, !dbg !1402
  %29 = load i32, i32* %pos, align 4, !dbg !1403
  %30 = load i32, i32* %hash_2_value, align 4, !dbg !1404
  %idxprom15 = zext i32 %30 to i64, !dbg !1405
  %31 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1405
  %hash = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %31, i32 0, i32 12, !dbg !1406
  %32 = load i32*, i32** %hash, align 8, !dbg !1406
  %arrayidx16 = getelementptr inbounds i32, i32* %32, i64 %idxprom15, !dbg !1405
  %33 = load i32, i32* %arrayidx16, align 4, !dbg !1405
  %sub = sub i32 %29, %33, !dbg !1407
  store i32 %sub, i32* %delta2, align 4, !dbg !1408
  %34 = load i32, i32* %hash_value, align 4, !dbg !1409
  %add17 = add i32 1024, %34, !dbg !1410
  %idxprom18 = zext i32 %add17 to i64, !dbg !1411
  %35 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1411
  %hash19 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %35, i32 0, i32 12, !dbg !1412
  %36 = load i32*, i32** %hash19, align 8, !dbg !1412
  %arrayidx20 = getelementptr inbounds i32, i32* %36, i64 %idxprom18, !dbg !1411
  %37 = load i32, i32* %arrayidx20, align 4, !dbg !1411
  store i32 %37, i32* %cur_match, align 4, !dbg !1413
  %38 = load i32, i32* %pos, align 4, !dbg !1414
  %39 = load i32, i32* %hash_2_value, align 4, !dbg !1415
  %idxprom21 = zext i32 %39 to i64, !dbg !1416
  %40 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1416
  %hash22 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %40, i32 0, i32 12, !dbg !1417
  %41 = load i32*, i32** %hash22, align 8, !dbg !1417
  %arrayidx23 = getelementptr inbounds i32, i32* %41, i64 %idxprom21, !dbg !1416
  store i32 %38, i32* %arrayidx23, align 4, !dbg !1418
  %42 = load i32, i32* %pos, align 4, !dbg !1419
  %43 = load i32, i32* %hash_value, align 4, !dbg !1420
  %add24 = add i32 1024, %43, !dbg !1421
  %idxprom25 = zext i32 %add24 to i64, !dbg !1422
  %44 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1422
  %hash26 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %44, i32 0, i32 12, !dbg !1423
  %45 = load i32*, i32** %hash26, align 8, !dbg !1423
  %arrayidx27 = getelementptr inbounds i32, i32* %45, i64 %idxprom25, !dbg !1422
  store i32 %42, i32* %arrayidx27, align 4, !dbg !1424
  %46 = load i32, i32* %delta2, align 4, !dbg !1425
  %47 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1427
  %cyclic_size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %47, i32 0, i32 15, !dbg !1428
  %48 = load i32, i32* %cyclic_size, align 4, !dbg !1428
  %cmp28 = icmp ult i32 %46, %48, !dbg !1429
  br i1 %cmp28, label %land.lhs.true, label %if.end58, !dbg !1430

land.lhs.true:                                    ; preds = %if.end7
  %49 = load i8*, i8** %cur, align 8, !dbg !1431
  %50 = load i32, i32* %delta2, align 4, !dbg !1433
  %idx.ext = zext i32 %50 to i64, !dbg !1434
  %idx.neg = sub i64 0, %idx.ext, !dbg !1434
  %add.ptr = getelementptr inbounds i8, i8* %49, i64 %idx.neg, !dbg !1434
  %51 = load i8, i8* %add.ptr, align 1, !dbg !1435
  %conv30 = zext i8 %51 to i32, !dbg !1435
  %52 = load i8*, i8** %cur, align 8, !dbg !1436
  %53 = load i8, i8* %52, align 1, !dbg !1437
  %conv31 = zext i8 %53 to i32, !dbg !1437
  %cmp32 = icmp eq i32 %conv30, %conv31, !dbg !1438
  br i1 %cmp32, label %if.then34, label %if.end58, !dbg !1439

if.then34:                                        ; preds = %land.lhs.true
  br label %for.cond, !dbg !1440

for.cond:                                         ; preds = %for.inc, %if.then34
  %54 = load i32, i32* %len_best, align 4, !dbg !1442
  %55 = load i32, i32* %len_limit, align 4, !dbg !1446
  %cmp35 = icmp ne i32 %54, %55, !dbg !1447
  br i1 %cmp35, label %for.body, label %for.end, !dbg !1448

for.body:                                         ; preds = %for.cond
  %56 = load i8*, i8** %cur, align 8, !dbg !1449
  %57 = load i32, i32* %len_best, align 4, !dbg !1451
  %idx.ext37 = zext i32 %57 to i64, !dbg !1452
  %add.ptr38 = getelementptr inbounds i8, i8* %56, i64 %idx.ext37, !dbg !1452
  %58 = load i32, i32* %delta2, align 4, !dbg !1453
  %idx.ext39 = zext i32 %58 to i64, !dbg !1454
  %idx.neg40 = sub i64 0, %idx.ext39, !dbg !1454
  %add.ptr41 = getelementptr inbounds i8, i8* %add.ptr38, i64 %idx.neg40, !dbg !1454
  %59 = load i8, i8* %add.ptr41, align 1, !dbg !1455
  %conv42 = zext i8 %59 to i32, !dbg !1455
  %60 = load i32, i32* %len_best, align 4, !dbg !1456
  %idxprom43 = zext i32 %60 to i64, !dbg !1457
  %61 = load i8*, i8** %cur, align 8, !dbg !1457
  %arrayidx44 = getelementptr inbounds i8, i8* %61, i64 %idxprom43, !dbg !1457
  %62 = load i8, i8* %arrayidx44, align 1, !dbg !1457
  %conv45 = zext i8 %62 to i32, !dbg !1457
  %cmp46 = icmp ne i32 %conv42, %conv45, !dbg !1458
  br i1 %cmp46, label %if.then48, label %if.end49, !dbg !1459

if.then48:                                        ; preds = %for.body
  br label %for.end, !dbg !1460

if.end49:                                         ; preds = %for.body
  br label %for.inc, !dbg !1461

for.inc:                                          ; preds = %if.end49
  %63 = load i32, i32* %len_best, align 4, !dbg !1463
  %inc = add i32 %63, 1, !dbg !1463
  store i32 %inc, i32* %len_best, align 4, !dbg !1463
  br label %for.cond, !dbg !1465

for.end:                                          ; preds = %if.then48, %for.cond
  %64 = load i32, i32* %len_best, align 4, !dbg !1466
  %65 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1467
  %arrayidx50 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %65, i64 0, !dbg !1467
  %len = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx50, i32 0, i32 0, !dbg !1468
  store i32 %64, i32* %len, align 4, !dbg !1469
  %66 = load i32, i32* %delta2, align 4, !dbg !1470
  %sub51 = sub i32 %66, 1, !dbg !1471
  %67 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1472
  %arrayidx52 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %67, i64 0, !dbg !1472
  %dist = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx52, i32 0, i32 1, !dbg !1473
  store i32 %sub51, i32* %dist, align 4, !dbg !1474
  store i32 1, i32* %matches_count, align 4, !dbg !1475
  %68 = load i32, i32* %len_best, align 4, !dbg !1476
  %69 = load i32, i32* %len_limit, align 4, !dbg !1478
  %cmp53 = icmp eq i32 %68, %69, !dbg !1479
  br i1 %cmp53, label %if.then55, label %if.end57, !dbg !1480

if.then55:                                        ; preds = %for.end
  br label %do.body, !dbg !1481

do.body:                                          ; preds = %if.then55
  %70 = load i32, i32* %len_limit, align 4, !dbg !1483
  %71 = load i32, i32* %pos, align 4, !dbg !1483
  %72 = load i8*, i8** %cur, align 8, !dbg !1483
  %73 = load i32, i32* %cur_match, align 4, !dbg !1483
  %74 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1483
  %depth = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %74, i32 0, i32 17, !dbg !1483
  %75 = load i32, i32* %depth, align 4, !dbg !1483
  %76 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1483
  %son = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %76, i32 0, i32 13, !dbg !1483
  %77 = load i32*, i32** %son, align 8, !dbg !1483
  %78 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1483
  %cyclic_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %78, i32 0, i32 14, !dbg !1483
  %79 = load i32, i32* %cyclic_pos, align 8, !dbg !1483
  %80 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1483
  %cyclic_size56 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %80, i32 0, i32 15, !dbg !1483
  %81 = load i32, i32* %cyclic_size56, align 4, !dbg !1483
  call void @bt_skip_func(i32 %70, i32 %71, i8* %72, i32 %73, i32 %75, i32* %77, i32 %79, i32 %81), !dbg !1483
  %82 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1483
  call void @move_pos(%struct.lzma_mf_s* %82), !dbg !1486
  br label %do.end, !dbg !1483

do.end:                                           ; preds = %do.body
  store i32 1, i32* %retval, align 4, !dbg !1488
  br label %do.end68, !dbg !1488

if.end57:                                         ; preds = %for.end
  br label %if.end58, !dbg !1489

if.end58:                                         ; preds = %if.end57, %land.lhs.true, %if.end7
  br label %do.body59, !dbg !1490

do.body59:                                        ; preds = %if.end58
  %83 = load i32, i32* %len_limit, align 4, !dbg !1491
  %84 = load i32, i32* %pos, align 4, !dbg !1491
  %85 = load i8*, i8** %cur, align 8, !dbg !1491
  %86 = load i32, i32* %cur_match, align 4, !dbg !1491
  %87 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1491
  %depth60 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %87, i32 0, i32 17, !dbg !1491
  %88 = load i32, i32* %depth60, align 4, !dbg !1491
  %89 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1491
  %son61 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %89, i32 0, i32 13, !dbg !1491
  %90 = load i32*, i32** %son61, align 8, !dbg !1491
  %91 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1491
  %cyclic_pos62 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %91, i32 0, i32 14, !dbg !1491
  %92 = load i32, i32* %cyclic_pos62, align 8, !dbg !1491
  %93 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1491
  %cyclic_size63 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %93, i32 0, i32 15, !dbg !1491
  %94 = load i32, i32* %cyclic_size63, align 4, !dbg !1491
  %95 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1491
  %96 = load i32, i32* %matches_count, align 4, !dbg !1491
  %idx.ext64 = zext i32 %96 to i64, !dbg !1491
  %add.ptr65 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %95, i64 %idx.ext64, !dbg !1491
  %97 = load i32, i32* %len_best, align 4, !dbg !1491
  %call66 = call %struct.lzma_match* @bt_find_func(i32 %83, i32 %84, i8* %85, i32 %86, i32 %88, i32* %90, i32 %92, i32 %94, %struct.lzma_match* %add.ptr65, i32 %97), !dbg !1491
  %98 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1491
  %sub.ptr.lhs.cast = ptrtoint %struct.lzma_match* %call66 to i64, !dbg !1491
  %sub.ptr.rhs.cast = ptrtoint %struct.lzma_match* %98 to i64, !dbg !1491
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1491
  %sub.ptr.div = sdiv exact i64 %sub.ptr.sub, 8, !dbg !1491
  %conv67 = trunc i64 %sub.ptr.div to i32, !dbg !1491
  store i32 %conv67, i32* %matches_count, align 4, !dbg !1491
  %99 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1491
  call void @move_pos(%struct.lzma_mf_s* %99), !dbg !1494
  %100 = load i32, i32* %matches_count, align 4, !dbg !1491
  store i32 %100, i32* %retval, align 4, !dbg !1491
  br label %do.end68, !dbg !1491

do.end68:                                         ; preds = %cond.end, %do.end, %do.body59
  %101 = load i32, i32* %retval, align 4, !dbg !1496
  ret i32 %101, !dbg !1496
}

; Function Attrs: nounwind uwtable
define void @lzma_mf_bt3_skip(%struct.lzma_mf_s* %mf, i32 %amount) #0 !dbg !75 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %amount.addr = alloca i32, align 4
  %cur = alloca i8*, align 8
  %pos = alloca i32, align 4
  %temp = alloca i32, align 4
  %hash_value = alloca i32, align 4
  %hash_2_value = alloca i32, align 4
  %cur_match = alloca i32, align 4
  %len_limit = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !1497, metadata !107), !dbg !1498
  store i32 %amount, i32* %amount.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %amount.addr, metadata !1499, metadata !107), !dbg !1500
  br label %do.body, !dbg !1501

do.body:                                          ; preds = %do.cond, %entry
  call void @llvm.dbg.declare(metadata i8** %cur, metadata !1502, metadata !107), !dbg !1504
  call void @llvm.dbg.declare(metadata i32* %pos, metadata !1505, metadata !107), !dbg !1506
  call void @llvm.dbg.declare(metadata i32* %temp, metadata !1507, metadata !107), !dbg !1508
  call void @llvm.dbg.declare(metadata i32* %hash_value, metadata !1509, metadata !107), !dbg !1510
  call void @llvm.dbg.declare(metadata i32* %hash_2_value, metadata !1511, metadata !107), !dbg !1512
  call void @llvm.dbg.declare(metadata i32* %cur_match, metadata !1513, metadata !107), !dbg !1514
  call void @llvm.dbg.declare(metadata i32* %len_limit, metadata !1515, metadata !107), !dbg !1516
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1516
  %call = call i32 @mf_avail(%struct.lzma_mf_s* %0), !dbg !1516
  store i32 %call, i32* %len_limit, align 4, !dbg !1516
  %1 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1517
  %nice_len = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %1, i32 0, i32 18, !dbg !1517
  %2 = load i32, i32* %nice_len, align 8, !dbg !1517
  %3 = load i32, i32* %len_limit, align 4, !dbg !1517
  %cmp = icmp ule i32 %2, %3, !dbg !1517
  br i1 %cmp, label %if.then, label %if.else, !dbg !1516

if.then:                                          ; preds = %do.body
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1519
  %nice_len1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %4, i32 0, i32 18, !dbg !1519
  %5 = load i32, i32* %nice_len1, align 8, !dbg !1519
  store i32 %5, i32* %len_limit, align 4, !dbg !1519
  br label %if.end7, !dbg !1519

if.else:                                          ; preds = %do.body
  %6 = load i32, i32* %len_limit, align 4, !dbg !1522
  %cmp2 = icmp ult i32 %6, 3, !dbg !1522
  br i1 %cmp2, label %if.then4, label %lor.lhs.false, !dbg !1522

lor.lhs.false:                                    ; preds = %if.else
  %7 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1525
  %action = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %7, i32 0, i32 20, !dbg !1525
  %8 = load i32, i32* %action, align 8, !dbg !1525
  %cmp3 = icmp eq i32 %8, 1, !dbg !1525
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !1525

if.then4:                                         ; preds = %lor.lhs.false, %if.else
  %9 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1527
  %action5 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %9, i32 0, i32 20, !dbg !1527
  %10 = load i32, i32* %action5, align 8, !dbg !1527
  %cmp6 = icmp ne i32 %10, 0, !dbg !1527
  br i1 %cmp6, label %cond.true, label %cond.false, !dbg !1527

cond.true:                                        ; preds = %if.then4
  br label %cond.end, !dbg !1530

cond.false:                                       ; preds = %if.then4
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.1, i32 0, i32 0), i32 718, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @__PRETTY_FUNCTION__.lzma_mf_bt3_skip, i32 0, i32 0)) #5, !dbg !1532
  unreachable, !dbg !1532
                                                  ; No predecessors!
  br label %cond.end, !dbg !1534

cond.end:                                         ; preds = %11, %cond.true
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1536
  call void @move_pending(%struct.lzma_mf_s* %12), !dbg !1536
  br label %do.cond, !dbg !1536

if.end:                                           ; preds = %lor.lhs.false
  br label %if.end7

if.end7:                                          ; preds = %if.end, %if.then
  %13 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1538
  %call8 = call i8* @mf_ptr(%struct.lzma_mf_s* %13), !dbg !1538
  store i8* %call8, i8** %cur, align 8, !dbg !1538
  %14 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1538
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %14, i32 0, i32 5, !dbg !1538
  %15 = load i32, i32* %read_pos, align 8, !dbg !1538
  %16 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1538
  %offset = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %16, i32 0, i32 4, !dbg !1538
  %17 = load i32, i32* %offset, align 4, !dbg !1538
  %add = add i32 %15, %17, !dbg !1538
  store i32 %add, i32* %pos, align 4, !dbg !1538
  %18 = load i8*, i8** %cur, align 8, !dbg !1540
  %arrayidx = getelementptr inbounds i8, i8* %18, i64 0, !dbg !1540
  %19 = load i8, i8* %arrayidx, align 1, !dbg !1540
  %idxprom = zext i8 %19 to i64, !dbg !1540
  %arrayidx9 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom, !dbg !1540
  %20 = load i32, i32* %arrayidx9, align 4, !dbg !1540
  %21 = load i8*, i8** %cur, align 8, !dbg !1540
  %arrayidx10 = getelementptr inbounds i8, i8* %21, i64 1, !dbg !1540
  %22 = load i8, i8* %arrayidx10, align 1, !dbg !1540
  %conv = zext i8 %22 to i32, !dbg !1540
  %xor = xor i32 %20, %conv, !dbg !1540
  store i32 %xor, i32* %temp, align 4, !dbg !1540
  %23 = load i32, i32* %temp, align 4, !dbg !1540
  %and = and i32 %23, 1023, !dbg !1540
  store i32 %and, i32* %hash_2_value, align 4, !dbg !1540
  %24 = load i32, i32* %temp, align 4, !dbg !1540
  %25 = load i8*, i8** %cur, align 8, !dbg !1540
  %arrayidx11 = getelementptr inbounds i8, i8* %25, i64 2, !dbg !1540
  %26 = load i8, i8* %arrayidx11, align 1, !dbg !1540
  %conv12 = zext i8 %26 to i32, !dbg !1540
  %shl = shl i32 %conv12, 8, !dbg !1540
  %xor13 = xor i32 %24, %shl, !dbg !1540
  %27 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1540
  %hash_mask = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %27, i32 0, i32 16, !dbg !1540
  %28 = load i32, i32* %hash_mask, align 8, !dbg !1540
  %and14 = and i32 %xor13, %28, !dbg !1540
  store i32 %and14, i32* %hash_value, align 4, !dbg !1540
  %29 = load i32, i32* %hash_value, align 4, !dbg !1541
  %add15 = add i32 1024, %29, !dbg !1542
  %idxprom16 = zext i32 %add15 to i64, !dbg !1543
  %30 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1543
  %hash = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %30, i32 0, i32 12, !dbg !1544
  %31 = load i32*, i32** %hash, align 8, !dbg !1544
  %arrayidx17 = getelementptr inbounds i32, i32* %31, i64 %idxprom16, !dbg !1543
  %32 = load i32, i32* %arrayidx17, align 4, !dbg !1543
  store i32 %32, i32* %cur_match, align 4, !dbg !1545
  %33 = load i32, i32* %pos, align 4, !dbg !1546
  %34 = load i32, i32* %hash_2_value, align 4, !dbg !1547
  %idxprom18 = zext i32 %34 to i64, !dbg !1548
  %35 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1548
  %hash19 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %35, i32 0, i32 12, !dbg !1549
  %36 = load i32*, i32** %hash19, align 8, !dbg !1549
  %arrayidx20 = getelementptr inbounds i32, i32* %36, i64 %idxprom18, !dbg !1548
  store i32 %33, i32* %arrayidx20, align 4, !dbg !1550
  %37 = load i32, i32* %pos, align 4, !dbg !1551
  %38 = load i32, i32* %hash_value, align 4, !dbg !1552
  %add21 = add i32 1024, %38, !dbg !1553
  %idxprom22 = zext i32 %add21 to i64, !dbg !1554
  %39 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1554
  %hash23 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %39, i32 0, i32 12, !dbg !1555
  %40 = load i32*, i32** %hash23, align 8, !dbg !1555
  %arrayidx24 = getelementptr inbounds i32, i32* %40, i64 %idxprom22, !dbg !1554
  store i32 %37, i32* %arrayidx24, align 4, !dbg !1556
  br label %do.body25, !dbg !1557

do.body25:                                        ; preds = %if.end7
  %41 = load i32, i32* %len_limit, align 4, !dbg !1558
  %42 = load i32, i32* %pos, align 4, !dbg !1558
  %43 = load i8*, i8** %cur, align 8, !dbg !1558
  %44 = load i32, i32* %cur_match, align 4, !dbg !1558
  %45 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1558
  %depth = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %45, i32 0, i32 17, !dbg !1558
  %46 = load i32, i32* %depth, align 4, !dbg !1558
  %47 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1558
  %son = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %47, i32 0, i32 13, !dbg !1558
  %48 = load i32*, i32** %son, align 8, !dbg !1558
  %49 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1558
  %cyclic_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %49, i32 0, i32 14, !dbg !1558
  %50 = load i32, i32* %cyclic_pos, align 8, !dbg !1558
  %51 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1558
  %cyclic_size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %51, i32 0, i32 15, !dbg !1558
  %52 = load i32, i32* %cyclic_size, align 4, !dbg !1558
  call void @bt_skip_func(i32 %41, i32 %42, i8* %43, i32 %44, i32 %46, i32* %48, i32 %50, i32 %52), !dbg !1558
  %53 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1558
  call void @move_pos(%struct.lzma_mf_s* %53), !dbg !1561
  br label %do.end, !dbg !1558

do.end:                                           ; preds = %do.body25
  br label %do.cond, !dbg !1563

do.cond:                                          ; preds = %do.end, %cond.end
  %54 = load i32, i32* %amount.addr, align 4, !dbg !1564
  %dec = add i32 %54, -1, !dbg !1564
  store i32 %dec, i32* %amount.addr, align 4, !dbg !1564
  %cmp26 = icmp ne i32 %dec, 0, !dbg !1566
  br i1 %cmp26, label %do.body, label %do.end28, !dbg !1567

do.end28:                                         ; preds = %do.cond
  ret void, !dbg !1568
}

; Function Attrs: nounwind uwtable
define i32 @lzma_mf_bt4_find(%struct.lzma_mf_s* %mf, %struct.lzma_match* %matches) #0 !dbg !76 {
entry:
  %retval = alloca i32, align 4
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %matches.addr = alloca %struct.lzma_match*, align 8
  %cur = alloca i8*, align 8
  %pos = alloca i32, align 4
  %temp = alloca i32, align 4
  %hash_value = alloca i32, align 4
  %hash_2_value = alloca i32, align 4
  %hash_3_value = alloca i32, align 4
  %delta2 = alloca i32, align 4
  %delta3 = alloca i32, align 4
  %cur_match = alloca i32, align 4
  %len_best = alloca i32, align 4
  %matches_count = alloca i32, align 4
  %len_limit = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !1569, metadata !107), !dbg !1570
  store %struct.lzma_match* %matches, %struct.lzma_match** %matches.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_match** %matches.addr, metadata !1571, metadata !107), !dbg !1572
  call void @llvm.dbg.declare(metadata i8** %cur, metadata !1573, metadata !107), !dbg !1574
  call void @llvm.dbg.declare(metadata i32* %pos, metadata !1575, metadata !107), !dbg !1576
  call void @llvm.dbg.declare(metadata i32* %temp, metadata !1577, metadata !107), !dbg !1578
  call void @llvm.dbg.declare(metadata i32* %hash_value, metadata !1579, metadata !107), !dbg !1580
  call void @llvm.dbg.declare(metadata i32* %hash_2_value, metadata !1581, metadata !107), !dbg !1582
  call void @llvm.dbg.declare(metadata i32* %hash_3_value, metadata !1583, metadata !107), !dbg !1584
  call void @llvm.dbg.declare(metadata i32* %delta2, metadata !1585, metadata !107), !dbg !1586
  call void @llvm.dbg.declare(metadata i32* %delta3, metadata !1587, metadata !107), !dbg !1588
  call void @llvm.dbg.declare(metadata i32* %cur_match, metadata !1589, metadata !107), !dbg !1590
  call void @llvm.dbg.declare(metadata i32* %len_best, metadata !1591, metadata !107), !dbg !1592
  store i32 1, i32* %len_best, align 4, !dbg !1592
  call void @llvm.dbg.declare(metadata i32* %matches_count, metadata !1593, metadata !107), !dbg !1594
  store i32 0, i32* %matches_count, align 4, !dbg !1594
  call void @llvm.dbg.declare(metadata i32* %len_limit, metadata !1595, metadata !107), !dbg !1596
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1596
  %call = call i32 @mf_avail(%struct.lzma_mf_s* %0), !dbg !1596
  store i32 %call, i32* %len_limit, align 4, !dbg !1596
  %1 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1597
  %nice_len = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %1, i32 0, i32 18, !dbg !1597
  %2 = load i32, i32* %nice_len, align 8, !dbg !1597
  %3 = load i32, i32* %len_limit, align 4, !dbg !1597
  %cmp = icmp ule i32 %2, %3, !dbg !1597
  br i1 %cmp, label %if.then, label %if.else, !dbg !1596

if.then:                                          ; preds = %entry
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1599
  %nice_len1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %4, i32 0, i32 18, !dbg !1599
  %5 = load i32, i32* %nice_len1, align 8, !dbg !1599
  store i32 %5, i32* %len_limit, align 4, !dbg !1599
  br label %if.end7, !dbg !1599

if.else:                                          ; preds = %entry
  %6 = load i32, i32* %len_limit, align 4, !dbg !1602
  %cmp2 = icmp ult i32 %6, 4, !dbg !1602
  br i1 %cmp2, label %if.then4, label %lor.lhs.false, !dbg !1602

lor.lhs.false:                                    ; preds = %if.else
  %7 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1605
  %action = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %7, i32 0, i32 20, !dbg !1605
  %8 = load i32, i32* %action, align 8, !dbg !1605
  %cmp3 = icmp eq i32 %8, 1, !dbg !1605
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !1605

if.then4:                                         ; preds = %lor.lhs.false, %if.else
  %9 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1607
  %action5 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %9, i32 0, i32 20, !dbg !1607
  %10 = load i32, i32* %action5, align 8, !dbg !1607
  %cmp6 = icmp ne i32 %10, 0, !dbg !1607
  br i1 %cmp6, label %cond.true, label %cond.false, !dbg !1607

cond.true:                                        ; preds = %if.then4
  br label %cond.end, !dbg !1610

cond.false:                                       ; preds = %if.then4
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.1, i32 0, i32 0), i32 745, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @__PRETTY_FUNCTION__.lzma_mf_bt4_find, i32 0, i32 0)) #5, !dbg !1612
  unreachable, !dbg !1612
                                                  ; No predecessors!
  br label %cond.end, !dbg !1614

cond.end:                                         ; preds = %11, %cond.true
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1616
  call void @move_pending(%struct.lzma_mf_s* %12), !dbg !1616
  store i32 0, i32* %retval, align 4, !dbg !1616
  br label %do.end120, !dbg !1616

if.end:                                           ; preds = %lor.lhs.false
  br label %if.end7

if.end7:                                          ; preds = %if.end, %if.then
  %13 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1618
  %call8 = call i8* @mf_ptr(%struct.lzma_mf_s* %13), !dbg !1618
  store i8* %call8, i8** %cur, align 8, !dbg !1618
  %14 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1618
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %14, i32 0, i32 5, !dbg !1618
  %15 = load i32, i32* %read_pos, align 8, !dbg !1618
  %16 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1618
  %offset = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %16, i32 0, i32 4, !dbg !1618
  %17 = load i32, i32* %offset, align 4, !dbg !1618
  %add = add i32 %15, %17, !dbg !1618
  store i32 %add, i32* %pos, align 4, !dbg !1618
  %18 = load i8*, i8** %cur, align 8, !dbg !1620
  %arrayidx = getelementptr inbounds i8, i8* %18, i64 0, !dbg !1620
  %19 = load i8, i8* %arrayidx, align 1, !dbg !1620
  %idxprom = zext i8 %19 to i64, !dbg !1620
  %arrayidx9 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom, !dbg !1620
  %20 = load i32, i32* %arrayidx9, align 4, !dbg !1620
  %21 = load i8*, i8** %cur, align 8, !dbg !1620
  %arrayidx10 = getelementptr inbounds i8, i8* %21, i64 1, !dbg !1620
  %22 = load i8, i8* %arrayidx10, align 1, !dbg !1620
  %conv = zext i8 %22 to i32, !dbg !1620
  %xor = xor i32 %20, %conv, !dbg !1620
  store i32 %xor, i32* %temp, align 4, !dbg !1620
  %23 = load i32, i32* %temp, align 4, !dbg !1620
  %and = and i32 %23, 1023, !dbg !1620
  store i32 %and, i32* %hash_2_value, align 4, !dbg !1620
  %24 = load i32, i32* %temp, align 4, !dbg !1620
  %25 = load i8*, i8** %cur, align 8, !dbg !1620
  %arrayidx11 = getelementptr inbounds i8, i8* %25, i64 2, !dbg !1620
  %26 = load i8, i8* %arrayidx11, align 1, !dbg !1620
  %conv12 = zext i8 %26 to i32, !dbg !1620
  %shl = shl i32 %conv12, 8, !dbg !1620
  %xor13 = xor i32 %24, %shl, !dbg !1620
  %and14 = and i32 %xor13, 65535, !dbg !1620
  store i32 %and14, i32* %hash_3_value, align 4, !dbg !1620
  %27 = load i32, i32* %temp, align 4, !dbg !1620
  %28 = load i8*, i8** %cur, align 8, !dbg !1620
  %arrayidx15 = getelementptr inbounds i8, i8* %28, i64 2, !dbg !1620
  %29 = load i8, i8* %arrayidx15, align 1, !dbg !1620
  %conv16 = zext i8 %29 to i32, !dbg !1620
  %shl17 = shl i32 %conv16, 8, !dbg !1620
  %xor18 = xor i32 %27, %shl17, !dbg !1620
  %30 = load i8*, i8** %cur, align 8, !dbg !1620
  %arrayidx19 = getelementptr inbounds i8, i8* %30, i64 3, !dbg !1620
  %31 = load i8, i8* %arrayidx19, align 1, !dbg !1620
  %idxprom20 = zext i8 %31 to i64, !dbg !1620
  %arrayidx21 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom20, !dbg !1620
  %32 = load i32, i32* %arrayidx21, align 4, !dbg !1620
  %shl22 = shl i32 %32, 5, !dbg !1620
  %xor23 = xor i32 %xor18, %shl22, !dbg !1620
  %33 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1620
  %hash_mask = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %33, i32 0, i32 16, !dbg !1620
  %34 = load i32, i32* %hash_mask, align 8, !dbg !1620
  %and24 = and i32 %xor23, %34, !dbg !1620
  store i32 %and24, i32* %hash_value, align 4, !dbg !1620
  %35 = load i32, i32* %pos, align 4, !dbg !1621
  %36 = load i32, i32* %hash_2_value, align 4, !dbg !1622
  %idxprom25 = zext i32 %36 to i64, !dbg !1623
  %37 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1623
  %hash = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %37, i32 0, i32 12, !dbg !1624
  %38 = load i32*, i32** %hash, align 8, !dbg !1624
  %arrayidx26 = getelementptr inbounds i32, i32* %38, i64 %idxprom25, !dbg !1623
  %39 = load i32, i32* %arrayidx26, align 4, !dbg !1623
  %sub = sub i32 %35, %39, !dbg !1625
  store i32 %sub, i32* %delta2, align 4, !dbg !1626
  %40 = load i32, i32* %pos, align 4, !dbg !1627
  %41 = load i32, i32* %hash_3_value, align 4, !dbg !1628
  %add27 = add i32 1024, %41, !dbg !1629
  %idxprom28 = zext i32 %add27 to i64, !dbg !1630
  %42 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1630
  %hash29 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %42, i32 0, i32 12, !dbg !1631
  %43 = load i32*, i32** %hash29, align 8, !dbg !1631
  %arrayidx30 = getelementptr inbounds i32, i32* %43, i64 %idxprom28, !dbg !1630
  %44 = load i32, i32* %arrayidx30, align 4, !dbg !1630
  %sub31 = sub i32 %40, %44, !dbg !1632
  store i32 %sub31, i32* %delta3, align 4, !dbg !1633
  %45 = load i32, i32* %hash_value, align 4, !dbg !1634
  %add32 = add i32 66560, %45, !dbg !1635
  %idxprom33 = zext i32 %add32 to i64, !dbg !1636
  %46 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1636
  %hash34 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %46, i32 0, i32 12, !dbg !1637
  %47 = load i32*, i32** %hash34, align 8, !dbg !1637
  %arrayidx35 = getelementptr inbounds i32, i32* %47, i64 %idxprom33, !dbg !1636
  %48 = load i32, i32* %arrayidx35, align 4, !dbg !1636
  store i32 %48, i32* %cur_match, align 4, !dbg !1638
  %49 = load i32, i32* %pos, align 4, !dbg !1639
  %50 = load i32, i32* %hash_2_value, align 4, !dbg !1640
  %idxprom36 = zext i32 %50 to i64, !dbg !1641
  %51 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1641
  %hash37 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %51, i32 0, i32 12, !dbg !1642
  %52 = load i32*, i32** %hash37, align 8, !dbg !1642
  %arrayidx38 = getelementptr inbounds i32, i32* %52, i64 %idxprom36, !dbg !1641
  store i32 %49, i32* %arrayidx38, align 4, !dbg !1643
  %53 = load i32, i32* %pos, align 4, !dbg !1644
  %54 = load i32, i32* %hash_3_value, align 4, !dbg !1645
  %add39 = add i32 1024, %54, !dbg !1646
  %idxprom40 = zext i32 %add39 to i64, !dbg !1647
  %55 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1647
  %hash41 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %55, i32 0, i32 12, !dbg !1648
  %56 = load i32*, i32** %hash41, align 8, !dbg !1648
  %arrayidx42 = getelementptr inbounds i32, i32* %56, i64 %idxprom40, !dbg !1647
  store i32 %53, i32* %arrayidx42, align 4, !dbg !1649
  %57 = load i32, i32* %pos, align 4, !dbg !1650
  %58 = load i32, i32* %hash_value, align 4, !dbg !1651
  %add43 = add i32 66560, %58, !dbg !1652
  %idxprom44 = zext i32 %add43 to i64, !dbg !1653
  %59 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1653
  %hash45 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %59, i32 0, i32 12, !dbg !1654
  %60 = load i32*, i32** %hash45, align 8, !dbg !1654
  %arrayidx46 = getelementptr inbounds i32, i32* %60, i64 %idxprom44, !dbg !1653
  store i32 %57, i32* %arrayidx46, align 4, !dbg !1655
  %61 = load i32, i32* %delta2, align 4, !dbg !1656
  %62 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1658
  %cyclic_size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %62, i32 0, i32 15, !dbg !1659
  %63 = load i32, i32* %cyclic_size, align 4, !dbg !1659
  %cmp47 = icmp ult i32 %61, %63, !dbg !1660
  br i1 %cmp47, label %land.lhs.true, label %if.end57, !dbg !1661

land.lhs.true:                                    ; preds = %if.end7
  %64 = load i8*, i8** %cur, align 8, !dbg !1662
  %65 = load i32, i32* %delta2, align 4, !dbg !1664
  %idx.ext = zext i32 %65 to i64, !dbg !1665
  %idx.neg = sub i64 0, %idx.ext, !dbg !1665
  %add.ptr = getelementptr inbounds i8, i8* %64, i64 %idx.neg, !dbg !1665
  %66 = load i8, i8* %add.ptr, align 1, !dbg !1666
  %conv49 = zext i8 %66 to i32, !dbg !1666
  %67 = load i8*, i8** %cur, align 8, !dbg !1667
  %68 = load i8, i8* %67, align 1, !dbg !1668
  %conv50 = zext i8 %68 to i32, !dbg !1668
  %cmp51 = icmp eq i32 %conv49, %conv50, !dbg !1669
  br i1 %cmp51, label %if.then53, label %if.end57, !dbg !1670

if.then53:                                        ; preds = %land.lhs.true
  store i32 2, i32* %len_best, align 4, !dbg !1671
  %69 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1673
  %arrayidx54 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %69, i64 0, !dbg !1673
  %len = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx54, i32 0, i32 0, !dbg !1674
  store i32 2, i32* %len, align 4, !dbg !1675
  %70 = load i32, i32* %delta2, align 4, !dbg !1676
  %sub55 = sub i32 %70, 1, !dbg !1677
  %71 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1678
  %arrayidx56 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %71, i64 0, !dbg !1678
  %dist = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx56, i32 0, i32 1, !dbg !1679
  store i32 %sub55, i32* %dist, align 4, !dbg !1680
  store i32 1, i32* %matches_count, align 4, !dbg !1681
  br label %if.end57, !dbg !1682

if.end57:                                         ; preds = %if.then53, %land.lhs.true, %if.end7
  %72 = load i32, i32* %delta2, align 4, !dbg !1683
  %73 = load i32, i32* %delta3, align 4, !dbg !1685
  %cmp58 = icmp ne i32 %72, %73, !dbg !1686
  br i1 %cmp58, label %land.lhs.true60, label %if.end77, !dbg !1687

land.lhs.true60:                                  ; preds = %if.end57
  %74 = load i32, i32* %delta3, align 4, !dbg !1688
  %75 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1690
  %cyclic_size61 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %75, i32 0, i32 15, !dbg !1691
  %76 = load i32, i32* %cyclic_size61, align 4, !dbg !1691
  %cmp62 = icmp ult i32 %74, %76, !dbg !1692
  br i1 %cmp62, label %land.lhs.true64, label %if.end77, !dbg !1693

land.lhs.true64:                                  ; preds = %land.lhs.true60
  %77 = load i8*, i8** %cur, align 8, !dbg !1694
  %78 = load i32, i32* %delta3, align 4, !dbg !1695
  %idx.ext65 = zext i32 %78 to i64, !dbg !1696
  %idx.neg66 = sub i64 0, %idx.ext65, !dbg !1696
  %add.ptr67 = getelementptr inbounds i8, i8* %77, i64 %idx.neg66, !dbg !1696
  %79 = load i8, i8* %add.ptr67, align 1, !dbg !1697
  %conv68 = zext i8 %79 to i32, !dbg !1697
  %80 = load i8*, i8** %cur, align 8, !dbg !1698
  %81 = load i8, i8* %80, align 1, !dbg !1699
  %conv69 = zext i8 %81 to i32, !dbg !1699
  %cmp70 = icmp eq i32 %conv68, %conv69, !dbg !1700
  br i1 %cmp70, label %if.then72, label %if.end77, !dbg !1701

if.then72:                                        ; preds = %land.lhs.true64
  store i32 3, i32* %len_best, align 4, !dbg !1703
  %82 = load i32, i32* %delta3, align 4, !dbg !1705
  %sub73 = sub i32 %82, 1, !dbg !1706
  %83 = load i32, i32* %matches_count, align 4, !dbg !1707
  %inc = add i32 %83, 1, !dbg !1707
  store i32 %inc, i32* %matches_count, align 4, !dbg !1707
  %idxprom74 = zext i32 %83 to i64, !dbg !1708
  %84 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1708
  %arrayidx75 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %84, i64 %idxprom74, !dbg !1708
  %dist76 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx75, i32 0, i32 1, !dbg !1709
  store i32 %sub73, i32* %dist76, align 4, !dbg !1710
  %85 = load i32, i32* %delta3, align 4, !dbg !1711
  store i32 %85, i32* %delta2, align 4, !dbg !1712
  br label %if.end77, !dbg !1713

if.end77:                                         ; preds = %if.then72, %land.lhs.true64, %land.lhs.true60, %if.end57
  %86 = load i32, i32* %matches_count, align 4, !dbg !1714
  %cmp78 = icmp ne i32 %86, 0, !dbg !1716
  br i1 %cmp78, label %if.then80, label %if.end106, !dbg !1717

if.then80:                                        ; preds = %if.end77
  br label %for.cond, !dbg !1718

for.cond:                                         ; preds = %for.inc, %if.then80
  %87 = load i32, i32* %len_best, align 4, !dbg !1720
  %88 = load i32, i32* %len_limit, align 4, !dbg !1724
  %cmp81 = icmp ne i32 %87, %88, !dbg !1725
  br i1 %cmp81, label %for.body, label %for.end, !dbg !1726

for.body:                                         ; preds = %for.cond
  %89 = load i8*, i8** %cur, align 8, !dbg !1727
  %90 = load i32, i32* %len_best, align 4, !dbg !1729
  %idx.ext83 = zext i32 %90 to i64, !dbg !1730
  %add.ptr84 = getelementptr inbounds i8, i8* %89, i64 %idx.ext83, !dbg !1730
  %91 = load i32, i32* %delta2, align 4, !dbg !1731
  %idx.ext85 = zext i32 %91 to i64, !dbg !1732
  %idx.neg86 = sub i64 0, %idx.ext85, !dbg !1732
  %add.ptr87 = getelementptr inbounds i8, i8* %add.ptr84, i64 %idx.neg86, !dbg !1732
  %92 = load i8, i8* %add.ptr87, align 1, !dbg !1733
  %conv88 = zext i8 %92 to i32, !dbg !1733
  %93 = load i32, i32* %len_best, align 4, !dbg !1734
  %idxprom89 = zext i32 %93 to i64, !dbg !1735
  %94 = load i8*, i8** %cur, align 8, !dbg !1735
  %arrayidx90 = getelementptr inbounds i8, i8* %94, i64 %idxprom89, !dbg !1735
  %95 = load i8, i8* %arrayidx90, align 1, !dbg !1735
  %conv91 = zext i8 %95 to i32, !dbg !1735
  %cmp92 = icmp ne i32 %conv88, %conv91, !dbg !1736
  br i1 %cmp92, label %if.then94, label %if.end95, !dbg !1737

if.then94:                                        ; preds = %for.body
  br label %for.end, !dbg !1738

if.end95:                                         ; preds = %for.body
  br label %for.inc, !dbg !1739

for.inc:                                          ; preds = %if.end95
  %96 = load i32, i32* %len_best, align 4, !dbg !1741
  %inc96 = add i32 %96, 1, !dbg !1741
  store i32 %inc96, i32* %len_best, align 4, !dbg !1741
  br label %for.cond, !dbg !1743

for.end:                                          ; preds = %if.then94, %for.cond
  %97 = load i32, i32* %len_best, align 4, !dbg !1744
  %98 = load i32, i32* %matches_count, align 4, !dbg !1745
  %sub97 = sub i32 %98, 1, !dbg !1746
  %idxprom98 = zext i32 %sub97 to i64, !dbg !1747
  %99 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1747
  %arrayidx99 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %99, i64 %idxprom98, !dbg !1747
  %len100 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %arrayidx99, i32 0, i32 0, !dbg !1748
  store i32 %97, i32* %len100, align 4, !dbg !1749
  %100 = load i32, i32* %len_best, align 4, !dbg !1750
  %101 = load i32, i32* %len_limit, align 4, !dbg !1752
  %cmp101 = icmp eq i32 %100, %101, !dbg !1753
  br i1 %cmp101, label %if.then103, label %if.end105, !dbg !1754

if.then103:                                       ; preds = %for.end
  br label %do.body, !dbg !1755

do.body:                                          ; preds = %if.then103
  %102 = load i32, i32* %len_limit, align 4, !dbg !1757
  %103 = load i32, i32* %pos, align 4, !dbg !1757
  %104 = load i8*, i8** %cur, align 8, !dbg !1757
  %105 = load i32, i32* %cur_match, align 4, !dbg !1757
  %106 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1757
  %depth = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %106, i32 0, i32 17, !dbg !1757
  %107 = load i32, i32* %depth, align 4, !dbg !1757
  %108 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1757
  %son = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %108, i32 0, i32 13, !dbg !1757
  %109 = load i32*, i32** %son, align 8, !dbg !1757
  %110 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1757
  %cyclic_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %110, i32 0, i32 14, !dbg !1757
  %111 = load i32, i32* %cyclic_pos, align 8, !dbg !1757
  %112 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1757
  %cyclic_size104 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %112, i32 0, i32 15, !dbg !1757
  %113 = load i32, i32* %cyclic_size104, align 4, !dbg !1757
  call void @bt_skip_func(i32 %102, i32 %103, i8* %104, i32 %105, i32 %107, i32* %109, i32 %111, i32 %113), !dbg !1757
  %114 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1757
  call void @move_pos(%struct.lzma_mf_s* %114), !dbg !1760
  br label %do.end, !dbg !1757

do.end:                                           ; preds = %do.body
  %115 = load i32, i32* %matches_count, align 4, !dbg !1762
  store i32 %115, i32* %retval, align 4, !dbg !1763
  br label %do.end120, !dbg !1763

if.end105:                                        ; preds = %for.end
  br label %if.end106, !dbg !1764

if.end106:                                        ; preds = %if.end105, %if.end77
  %116 = load i32, i32* %len_best, align 4, !dbg !1765
  %cmp107 = icmp ult i32 %116, 3, !dbg !1767
  br i1 %cmp107, label %if.then109, label %if.end110, !dbg !1768

if.then109:                                       ; preds = %if.end106
  store i32 3, i32* %len_best, align 4, !dbg !1769
  br label %if.end110, !dbg !1770

if.end110:                                        ; preds = %if.then109, %if.end106
  br label %do.body111, !dbg !1771

do.body111:                                       ; preds = %if.end110
  %117 = load i32, i32* %len_limit, align 4, !dbg !1772
  %118 = load i32, i32* %pos, align 4, !dbg !1772
  %119 = load i8*, i8** %cur, align 8, !dbg !1772
  %120 = load i32, i32* %cur_match, align 4, !dbg !1772
  %121 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1772
  %depth112 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %121, i32 0, i32 17, !dbg !1772
  %122 = load i32, i32* %depth112, align 4, !dbg !1772
  %123 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1772
  %son113 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %123, i32 0, i32 13, !dbg !1772
  %124 = load i32*, i32** %son113, align 8, !dbg !1772
  %125 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1772
  %cyclic_pos114 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %125, i32 0, i32 14, !dbg !1772
  %126 = load i32, i32* %cyclic_pos114, align 8, !dbg !1772
  %127 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1772
  %cyclic_size115 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %127, i32 0, i32 15, !dbg !1772
  %128 = load i32, i32* %cyclic_size115, align 4, !dbg !1772
  %129 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1772
  %130 = load i32, i32* %matches_count, align 4, !dbg !1772
  %idx.ext116 = zext i32 %130 to i64, !dbg !1772
  %add.ptr117 = getelementptr inbounds %struct.lzma_match, %struct.lzma_match* %129, i64 %idx.ext116, !dbg !1772
  %131 = load i32, i32* %len_best, align 4, !dbg !1772
  %call118 = call %struct.lzma_match* @bt_find_func(i32 %117, i32 %118, i8* %119, i32 %120, i32 %122, i32* %124, i32 %126, i32 %128, %struct.lzma_match* %add.ptr117, i32 %131), !dbg !1772
  %132 = load %struct.lzma_match*, %struct.lzma_match** %matches.addr, align 8, !dbg !1772
  %sub.ptr.lhs.cast = ptrtoint %struct.lzma_match* %call118 to i64, !dbg !1772
  %sub.ptr.rhs.cast = ptrtoint %struct.lzma_match* %132 to i64, !dbg !1772
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1772
  %sub.ptr.div = sdiv exact i64 %sub.ptr.sub, 8, !dbg !1772
  %conv119 = trunc i64 %sub.ptr.div to i32, !dbg !1772
  store i32 %conv119, i32* %matches_count, align 4, !dbg !1772
  %133 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1772
  call void @move_pos(%struct.lzma_mf_s* %133), !dbg !1775
  %134 = load i32, i32* %matches_count, align 4, !dbg !1772
  store i32 %134, i32* %retval, align 4, !dbg !1772
  br label %do.end120, !dbg !1772

do.end120:                                        ; preds = %cond.end, %do.end, %do.body111
  %135 = load i32, i32* %retval, align 4, !dbg !1777
  ret i32 %135, !dbg !1777
}

; Function Attrs: nounwind uwtable
define void @lzma_mf_bt4_skip(%struct.lzma_mf_s* %mf, i32 %amount) #0 !dbg !77 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %amount.addr = alloca i32, align 4
  %cur = alloca i8*, align 8
  %pos = alloca i32, align 4
  %temp = alloca i32, align 4
  %hash_value = alloca i32, align 4
  %hash_2_value = alloca i32, align 4
  %hash_3_value = alloca i32, align 4
  %cur_match = alloca i32, align 4
  %len_limit = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !1778, metadata !107), !dbg !1779
  store i32 %amount, i32* %amount.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %amount.addr, metadata !1780, metadata !107), !dbg !1781
  br label %do.body, !dbg !1782

do.body:                                          ; preds = %do.cond, %entry
  call void @llvm.dbg.declare(metadata i8** %cur, metadata !1783, metadata !107), !dbg !1785
  call void @llvm.dbg.declare(metadata i32* %pos, metadata !1786, metadata !107), !dbg !1787
  call void @llvm.dbg.declare(metadata i32* %temp, metadata !1788, metadata !107), !dbg !1789
  call void @llvm.dbg.declare(metadata i32* %hash_value, metadata !1790, metadata !107), !dbg !1791
  call void @llvm.dbg.declare(metadata i32* %hash_2_value, metadata !1792, metadata !107), !dbg !1793
  call void @llvm.dbg.declare(metadata i32* %hash_3_value, metadata !1794, metadata !107), !dbg !1795
  call void @llvm.dbg.declare(metadata i32* %cur_match, metadata !1796, metadata !107), !dbg !1797
  call void @llvm.dbg.declare(metadata i32* %len_limit, metadata !1798, metadata !107), !dbg !1799
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1799
  %call = call i32 @mf_avail(%struct.lzma_mf_s* %0), !dbg !1799
  store i32 %call, i32* %len_limit, align 4, !dbg !1799
  %1 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1800
  %nice_len = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %1, i32 0, i32 18, !dbg !1800
  %2 = load i32, i32* %nice_len, align 8, !dbg !1800
  %3 = load i32, i32* %len_limit, align 4, !dbg !1800
  %cmp = icmp ule i32 %2, %3, !dbg !1800
  br i1 %cmp, label %if.then, label %if.else, !dbg !1799

if.then:                                          ; preds = %do.body
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1802
  %nice_len1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %4, i32 0, i32 18, !dbg !1802
  %5 = load i32, i32* %nice_len1, align 8, !dbg !1802
  store i32 %5, i32* %len_limit, align 4, !dbg !1802
  br label %if.end7, !dbg !1802

if.else:                                          ; preds = %do.body
  %6 = load i32, i32* %len_limit, align 4, !dbg !1805
  %cmp2 = icmp ult i32 %6, 4, !dbg !1805
  br i1 %cmp2, label %if.then4, label %lor.lhs.false, !dbg !1805

lor.lhs.false:                                    ; preds = %if.else
  %7 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1808
  %action = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %7, i32 0, i32 20, !dbg !1808
  %8 = load i32, i32* %action, align 8, !dbg !1808
  %cmp3 = icmp eq i32 %8, 1, !dbg !1808
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !1808

if.then4:                                         ; preds = %lor.lhs.false, %if.else
  %9 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1810
  %action5 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %9, i32 0, i32 20, !dbg !1810
  %10 = load i32, i32* %action5, align 8, !dbg !1810
  %cmp6 = icmp ne i32 %10, 0, !dbg !1810
  br i1 %cmp6, label %cond.true, label %cond.false, !dbg !1810

cond.true:                                        ; preds = %if.then4
  br label %cond.end, !dbg !1813

cond.false:                                       ; preds = %if.then4
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.1, i32 0, i32 0), i32 800, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @__PRETTY_FUNCTION__.lzma_mf_bt4_skip, i32 0, i32 0)) #5, !dbg !1815
  unreachable, !dbg !1815
                                                  ; No predecessors!
  br label %cond.end, !dbg !1817

cond.end:                                         ; preds = %11, %cond.true
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1819
  call void @move_pending(%struct.lzma_mf_s* %12), !dbg !1819
  br label %do.cond, !dbg !1819

if.end:                                           ; preds = %lor.lhs.false
  br label %if.end7

if.end7:                                          ; preds = %if.end, %if.then
  %13 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1821
  %call8 = call i8* @mf_ptr(%struct.lzma_mf_s* %13), !dbg !1821
  store i8* %call8, i8** %cur, align 8, !dbg !1821
  %14 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1821
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %14, i32 0, i32 5, !dbg !1821
  %15 = load i32, i32* %read_pos, align 8, !dbg !1821
  %16 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1821
  %offset = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %16, i32 0, i32 4, !dbg !1821
  %17 = load i32, i32* %offset, align 4, !dbg !1821
  %add = add i32 %15, %17, !dbg !1821
  store i32 %add, i32* %pos, align 4, !dbg !1821
  %18 = load i8*, i8** %cur, align 8, !dbg !1823
  %arrayidx = getelementptr inbounds i8, i8* %18, i64 0, !dbg !1823
  %19 = load i8, i8* %arrayidx, align 1, !dbg !1823
  %idxprom = zext i8 %19 to i64, !dbg !1823
  %arrayidx9 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom, !dbg !1823
  %20 = load i32, i32* %arrayidx9, align 4, !dbg !1823
  %21 = load i8*, i8** %cur, align 8, !dbg !1823
  %arrayidx10 = getelementptr inbounds i8, i8* %21, i64 1, !dbg !1823
  %22 = load i8, i8* %arrayidx10, align 1, !dbg !1823
  %conv = zext i8 %22 to i32, !dbg !1823
  %xor = xor i32 %20, %conv, !dbg !1823
  store i32 %xor, i32* %temp, align 4, !dbg !1823
  %23 = load i32, i32* %temp, align 4, !dbg !1823
  %and = and i32 %23, 1023, !dbg !1823
  store i32 %and, i32* %hash_2_value, align 4, !dbg !1823
  %24 = load i32, i32* %temp, align 4, !dbg !1823
  %25 = load i8*, i8** %cur, align 8, !dbg !1823
  %arrayidx11 = getelementptr inbounds i8, i8* %25, i64 2, !dbg !1823
  %26 = load i8, i8* %arrayidx11, align 1, !dbg !1823
  %conv12 = zext i8 %26 to i32, !dbg !1823
  %shl = shl i32 %conv12, 8, !dbg !1823
  %xor13 = xor i32 %24, %shl, !dbg !1823
  %and14 = and i32 %xor13, 65535, !dbg !1823
  store i32 %and14, i32* %hash_3_value, align 4, !dbg !1823
  %27 = load i32, i32* %temp, align 4, !dbg !1823
  %28 = load i8*, i8** %cur, align 8, !dbg !1823
  %arrayidx15 = getelementptr inbounds i8, i8* %28, i64 2, !dbg !1823
  %29 = load i8, i8* %arrayidx15, align 1, !dbg !1823
  %conv16 = zext i8 %29 to i32, !dbg !1823
  %shl17 = shl i32 %conv16, 8, !dbg !1823
  %xor18 = xor i32 %27, %shl17, !dbg !1823
  %30 = load i8*, i8** %cur, align 8, !dbg !1823
  %arrayidx19 = getelementptr inbounds i8, i8* %30, i64 3, !dbg !1823
  %31 = load i8, i8* %arrayidx19, align 1, !dbg !1823
  %idxprom20 = zext i8 %31 to i64, !dbg !1823
  %arrayidx21 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom20, !dbg !1823
  %32 = load i32, i32* %arrayidx21, align 4, !dbg !1823
  %shl22 = shl i32 %32, 5, !dbg !1823
  %xor23 = xor i32 %xor18, %shl22, !dbg !1823
  %33 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1823
  %hash_mask = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %33, i32 0, i32 16, !dbg !1823
  %34 = load i32, i32* %hash_mask, align 8, !dbg !1823
  %and24 = and i32 %xor23, %34, !dbg !1823
  store i32 %and24, i32* %hash_value, align 4, !dbg !1823
  %35 = load i32, i32* %hash_value, align 4, !dbg !1824
  %add25 = add i32 66560, %35, !dbg !1825
  %idxprom26 = zext i32 %add25 to i64, !dbg !1826
  %36 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1826
  %hash = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %36, i32 0, i32 12, !dbg !1827
  %37 = load i32*, i32** %hash, align 8, !dbg !1827
  %arrayidx27 = getelementptr inbounds i32, i32* %37, i64 %idxprom26, !dbg !1826
  %38 = load i32, i32* %arrayidx27, align 4, !dbg !1826
  store i32 %38, i32* %cur_match, align 4, !dbg !1828
  %39 = load i32, i32* %pos, align 4, !dbg !1829
  %40 = load i32, i32* %hash_2_value, align 4, !dbg !1830
  %idxprom28 = zext i32 %40 to i64, !dbg !1831
  %41 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1831
  %hash29 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %41, i32 0, i32 12, !dbg !1832
  %42 = load i32*, i32** %hash29, align 8, !dbg !1832
  %arrayidx30 = getelementptr inbounds i32, i32* %42, i64 %idxprom28, !dbg !1831
  store i32 %39, i32* %arrayidx30, align 4, !dbg !1833
  %43 = load i32, i32* %pos, align 4, !dbg !1834
  %44 = load i32, i32* %hash_3_value, align 4, !dbg !1835
  %add31 = add i32 1024, %44, !dbg !1836
  %idxprom32 = zext i32 %add31 to i64, !dbg !1837
  %45 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1837
  %hash33 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %45, i32 0, i32 12, !dbg !1838
  %46 = load i32*, i32** %hash33, align 8, !dbg !1838
  %arrayidx34 = getelementptr inbounds i32, i32* %46, i64 %idxprom32, !dbg !1837
  store i32 %43, i32* %arrayidx34, align 4, !dbg !1839
  %47 = load i32, i32* %pos, align 4, !dbg !1840
  %48 = load i32, i32* %hash_value, align 4, !dbg !1841
  %add35 = add i32 66560, %48, !dbg !1842
  %idxprom36 = zext i32 %add35 to i64, !dbg !1843
  %49 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1843
  %hash37 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %49, i32 0, i32 12, !dbg !1844
  %50 = load i32*, i32** %hash37, align 8, !dbg !1844
  %arrayidx38 = getelementptr inbounds i32, i32* %50, i64 %idxprom36, !dbg !1843
  store i32 %47, i32* %arrayidx38, align 4, !dbg !1845
  br label %do.body39, !dbg !1846

do.body39:                                        ; preds = %if.end7
  %51 = load i32, i32* %len_limit, align 4, !dbg !1847
  %52 = load i32, i32* %pos, align 4, !dbg !1847
  %53 = load i8*, i8** %cur, align 8, !dbg !1847
  %54 = load i32, i32* %cur_match, align 4, !dbg !1847
  %55 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1847
  %depth = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %55, i32 0, i32 17, !dbg !1847
  %56 = load i32, i32* %depth, align 4, !dbg !1847
  %57 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1847
  %son = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %57, i32 0, i32 13, !dbg !1847
  %58 = load i32*, i32** %son, align 8, !dbg !1847
  %59 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1847
  %cyclic_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %59, i32 0, i32 14, !dbg !1847
  %60 = load i32, i32* %cyclic_pos, align 8, !dbg !1847
  %61 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1847
  %cyclic_size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %61, i32 0, i32 15, !dbg !1847
  %62 = load i32, i32* %cyclic_size, align 4, !dbg !1847
  call void @bt_skip_func(i32 %51, i32 %52, i8* %53, i32 %54, i32 %56, i32* %58, i32 %60, i32 %62), !dbg !1847
  %63 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1847
  call void @move_pos(%struct.lzma_mf_s* %63), !dbg !1850
  br label %do.end, !dbg !1847

do.end:                                           ; preds = %do.body39
  br label %do.cond, !dbg !1852

do.cond:                                          ; preds = %do.end, %cond.end
  %64 = load i32, i32* %amount.addr, align 4, !dbg !1853
  %dec = add i32 %64, -1, !dbg !1853
  store i32 %dec, i32* %amount.addr, align 4, !dbg !1853
  %cmp40 = icmp ne i32 %dec, 0, !dbg !1855
  br i1 %cmp40, label %do.body, label %do.end42, !dbg !1856

do.end42:                                         ; preds = %do.cond
  ret void, !dbg !1857
}

; Function Attrs: nounwind uwtable
define internal void @normalize(%struct.lzma_mf_s* %mf) #0 !dbg !90 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %i = alloca i32, align 4
  %subvalue = alloca i32, align 4
  %count = alloca i32, align 4
  %hash = alloca i32*, align 8
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !1858, metadata !107), !dbg !1859
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1860, metadata !107), !dbg !1861
  call void @llvm.dbg.declare(metadata i32* %subvalue, metadata !1862, metadata !107), !dbg !1863
  call void @llvm.dbg.declare(metadata i32* %count, metadata !1864, metadata !107), !dbg !1865
  call void @llvm.dbg.declare(metadata i32** %hash, metadata !1866, metadata !107), !dbg !1867
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1868
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 5, !dbg !1868
  %1 = load i32, i32* %read_pos, align 8, !dbg !1868
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1868
  %offset = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 4, !dbg !1868
  %3 = load i32, i32* %offset, align 4, !dbg !1868
  %add = add i32 %1, %3, !dbg !1868
  %cmp = icmp eq i32 %add, -1, !dbg !1868
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1868

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1869

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.1, i32 0, i32 0), i32 120, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @__PRETTY_FUNCTION__.normalize, i32 0, i32 0)) #5, !dbg !1871
  unreachable, !dbg !1871
                                                  ; No predecessors!
  br label %cond.end, !dbg !1873

cond.end:                                         ; preds = %4, %cond.true
  %5 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1875
  %cyclic_size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %5, i32 0, i32 15, !dbg !1876
  %6 = load i32, i32* %cyclic_size, align 4, !dbg !1876
  %sub = sub i32 -1, %6, !dbg !1877
  store i32 %sub, i32* %subvalue, align 4, !dbg !1878
  %7 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1879
  %hash_size_sum = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %7, i32 0, i32 21, !dbg !1880
  %8 = load i32, i32* %hash_size_sum, align 4, !dbg !1880
  %9 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1881
  %sons_count = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %9, i32 0, i32 22, !dbg !1882
  %10 = load i32, i32* %sons_count, align 8, !dbg !1882
  %add1 = add i32 %8, %10, !dbg !1883
  store i32 %add1, i32* %count, align 4, !dbg !1884
  %11 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1885
  %hash2 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %11, i32 0, i32 12, !dbg !1886
  %12 = load i32*, i32** %hash2, align 8, !dbg !1886
  store i32* %12, i32** %hash, align 8, !dbg !1887
  store i32 0, i32* %i, align 4, !dbg !1888
  br label %for.cond, !dbg !1890

for.cond:                                         ; preds = %for.inc, %cond.end
  %13 = load i32, i32* %i, align 4, !dbg !1891
  %14 = load i32, i32* %count, align 4, !dbg !1894
  %cmp3 = icmp ult i32 %13, %14, !dbg !1895
  br i1 %cmp3, label %for.body, label %for.end, !dbg !1896

for.body:                                         ; preds = %for.cond
  %15 = load i32, i32* %i, align 4, !dbg !1897
  %idxprom = zext i32 %15 to i64, !dbg !1900
  %16 = load i32*, i32** %hash, align 8, !dbg !1900
  %arrayidx = getelementptr inbounds i32, i32* %16, i64 %idxprom, !dbg !1900
  %17 = load i32, i32* %arrayidx, align 4, !dbg !1900
  %18 = load i32, i32* %subvalue, align 4, !dbg !1901
  %cmp4 = icmp ule i32 %17, %18, !dbg !1902
  br i1 %cmp4, label %if.then, label %if.else, !dbg !1903

if.then:                                          ; preds = %for.body
  %19 = load i32, i32* %i, align 4, !dbg !1904
  %idxprom5 = zext i32 %19 to i64, !dbg !1905
  %20 = load i32*, i32** %hash, align 8, !dbg !1905
  %arrayidx6 = getelementptr inbounds i32, i32* %20, i64 %idxprom5, !dbg !1905
  store i32 0, i32* %arrayidx6, align 4, !dbg !1906
  br label %if.end, !dbg !1905

if.else:                                          ; preds = %for.body
  %21 = load i32, i32* %subvalue, align 4, !dbg !1907
  %22 = load i32, i32* %i, align 4, !dbg !1908
  %idxprom7 = zext i32 %22 to i64, !dbg !1909
  %23 = load i32*, i32** %hash, align 8, !dbg !1909
  %arrayidx8 = getelementptr inbounds i32, i32* %23, i64 %idxprom7, !dbg !1909
  %24 = load i32, i32* %arrayidx8, align 4, !dbg !1910
  %sub9 = sub i32 %24, %21, !dbg !1910
  store i32 %sub9, i32* %arrayidx8, align 4, !dbg !1910
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %for.inc, !dbg !1911

for.inc:                                          ; preds = %if.end
  %25 = load i32, i32* %i, align 4, !dbg !1912
  %inc = add i32 %25, 1, !dbg !1912
  store i32 %inc, i32* %i, align 4, !dbg !1912
  br label %for.cond, !dbg !1914

for.end:                                          ; preds = %for.cond
  %26 = load i32, i32* %subvalue, align 4, !dbg !1915
  %27 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1916
  %offset10 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %27, i32 0, i32 4, !dbg !1917
  %28 = load i32, i32* %offset10, align 4, !dbg !1918
  %sub11 = sub i32 %28, %26, !dbg !1918
  store i32 %sub11, i32* %offset10, align 4, !dbg !1918
  ret void, !dbg !1919
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind }
attributes #6 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!103, !104}
!llvm.ident = !{!105}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !10, subprograms: !18)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_encoder_mf.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !{!6, !7, !8, !9}
!6 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!7 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!8 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!9 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!10 = !{!11, !14}
!11 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !12, line: 51, baseType: !13)
!12 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!13 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64, align: 64)
!15 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !16)
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !12, line: 49, baseType: !17)
!17 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!18 = !{!19, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !83, !86, !89, !90, !91, !99, !100}
!19 = distinct !DISubprogram(name: "lzma_mf_find", scope: !1, file: !1, line: 22, type: !20, isLocal: false, isDefinition: true, scopeLine: 23, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!20 = !DISubroutineType(types: !21)
!21 = !{!11, !22, !55, !44}
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!23 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mf", file: !24, line: 28, baseType: !25)
!24 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_encoder.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!25 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_mf_s", file: !24, line: 29, size: 960, align: 64, elements: !26)
!26 = !{!27, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !50, !54, !56, !57, !58, !59, !60, !61, !62, !63, !65, !66}
!27 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !25, file: !24, line: 35, baseType: !28, size: 64, align: 64)
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!29 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !12, line: 48, baseType: !30)
!30 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!31 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !25, file: !24, line: 39, baseType: !11, size: 32, align: 32, offset: 64)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "keep_size_before", scope: !25, file: !24, line: 45, baseType: !11, size: 32, align: 32, offset: 96)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "keep_size_after", scope: !25, file: !24, line: 51, baseType: !11, size: 32, align: 32, offset: 128)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !25, file: !24, line: 58, baseType: !11, size: 32, align: 32, offset: 160)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "read_pos", scope: !25, file: !24, line: 63, baseType: !11, size: 32, align: 32, offset: 192)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "read_ahead", scope: !25, file: !24, line: 67, baseType: !11, size: 32, align: 32, offset: 224)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "read_limit", scope: !25, file: !24, line: 75, baseType: !11, size: 32, align: 32, offset: 256)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "write_pos", scope: !25, file: !24, line: 80, baseType: !11, size: 32, align: 32, offset: 288)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !25, file: !24, line: 84, baseType: !11, size: 32, align: 32, offset: 320)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "find", scope: !25, file: !24, line: 92, baseType: !41, size: 64, align: 64, offset: 384)
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!42 = !DISubroutineType(types: !43)
!43 = !{!11, !22, !44}
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match", file: !24, line: 25, baseType: !46)
!46 = !DICompositeType(tag: DW_TAG_structure_type, file: !24, line: 22, size: 64, align: 32, elements: !47)
!47 = !{!48, !49}
!48 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !46, file: !24, line: 23, baseType: !11, size: 32, align: 32)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "dist", scope: !46, file: !24, line: 24, baseType: !11, size: 32, align: 32, offset: 32)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "skip", scope: !25, file: !24, line: 97, baseType: !51, size: 64, align: 64, offset: 448)
!51 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!52 = !DISubroutineType(types: !53)
!53 = !{null, !22, !11}
!54 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !25, file: !24, line: 99, baseType: !55, size: 64, align: 64, offset: 512)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "son", scope: !25, file: !24, line: 100, baseType: !55, size: 64, align: 64, offset: 576)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "cyclic_pos", scope: !25, file: !24, line: 101, baseType: !11, size: 32, align: 32, offset: 640)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "cyclic_size", scope: !25, file: !24, line: 102, baseType: !11, size: 32, align: 32, offset: 672)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "hash_mask", scope: !25, file: !24, line: 103, baseType: !11, size: 32, align: 32, offset: 704)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !25, file: !24, line: 106, baseType: !11, size: 32, align: 32, offset: 736)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !25, file: !24, line: 109, baseType: !11, size: 32, align: 32, offset: 768)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "match_len_max", scope: !25, file: !24, line: 114, baseType: !11, size: 32, align: 32, offset: 800)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "action", scope: !25, file: !24, line: 119, baseType: !64, size: 32, align: 32, offset: 832)
!64 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !3)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "hash_size_sum", scope: !25, file: !24, line: 122, baseType: !11, size: 32, align: 32, offset: 864)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "sons_count", scope: !25, file: !24, line: 125, baseType: !11, size: 32, align: 32, offset: 896)
!67 = !{}
!68 = distinct !DISubprogram(name: "lzma_mf_hc3_find", scope: !1, file: !1, line: 314, type: !42, isLocal: false, isDefinition: true, scopeLine: 315, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!69 = distinct !DISubprogram(name: "lzma_mf_hc3_skip", scope: !1, file: !1, line: 353, type: !52, isLocal: false, isDefinition: true, scopeLine: 354, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!70 = distinct !DISubprogram(name: "lzma_mf_hc4_find", scope: !1, file: !1, line: 385, type: !42, isLocal: false, isDefinition: true, scopeLine: 386, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!71 = distinct !DISubprogram(name: "lzma_mf_hc4_skip", scope: !1, file: !1, line: 441, type: !52, isLocal: false, isDefinition: true, scopeLine: 442, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!72 = distinct !DISubprogram(name: "lzma_mf_bt2_find", scope: !1, file: !1, line: 627, type: !42, isLocal: false, isDefinition: true, scopeLine: 628, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!73 = distinct !DISubprogram(name: "lzma_mf_bt2_skip", scope: !1, file: !1, line: 647, type: !52, isLocal: false, isDefinition: true, scopeLine: 648, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!74 = distinct !DISubprogram(name: "lzma_mf_bt3_find", scope: !1, file: !1, line: 671, type: !42, isLocal: false, isDefinition: true, scopeLine: 672, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!75 = distinct !DISubprogram(name: "lzma_mf_bt3_skip", scope: !1, file: !1, line: 710, type: !52, isLocal: false, isDefinition: true, scopeLine: 711, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!76 = distinct !DISubprogram(name: "lzma_mf_bt4_find", scope: !1, file: !1, line: 736, type: !42, isLocal: false, isDefinition: true, scopeLine: 737, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!77 = distinct !DISubprogram(name: "lzma_mf_bt4_skip", scope: !1, file: !1, line: 792, type: !52, isLocal: false, isDefinition: true, scopeLine: 793, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!78 = distinct !DISubprogram(name: "mf_ptr", scope: !24, file: !24, line: 222, type: !79, isLocal: true, isDefinition: true, scopeLine: 223, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!79 = !DISubroutineType(types: !80)
!80 = !{!28, !81}
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!82 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !23)
!83 = distinct !DISubprogram(name: "mf_avail", scope: !24, file: !24, line: 230, type: !84, isLocal: true, isDefinition: true, scopeLine: 231, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!84 = !DISubroutineType(types: !85)
!85 = !{!11, !81}
!86 = distinct !DISubprogram(name: "move_pending", scope: !1, file: !1, line: 184, type: !87, isLocal: true, isDefinition: true, scopeLine: 185, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!87 = !DISubroutineType(types: !88)
!88 = !{null, !22}
!89 = distinct !DISubprogram(name: "move_pos", scope: !1, file: !1, line: 156, type: !87, isLocal: true, isDefinition: true, scopeLine: 157, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!90 = distinct !DISubprogram(name: "normalize", scope: !1, file: !1, line: 113, type: !87, isLocal: true, isDefinition: true, scopeLine: 114, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!91 = distinct !DISubprogram(name: "hc_find_func", scope: !1, file: !1, line: 255, type: !92, isLocal: true, isDefinition: true, scopeLine: 266, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!92 = !DISubroutineType(types: !93)
!93 = !{!44, !94, !94, !95, !11, !11, !98, !94, !94, !44, !11}
!94 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !11)
!95 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !96)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !97, size: 64, align: 64)
!97 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !29)
!98 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !55)
!99 = distinct !DISubprogram(name: "bt_find_func", scope: !1, file: !1, line: 478, type: !92, isLocal: true, isDefinition: true, scopeLine: 489, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!100 = distinct !DISubprogram(name: "bt_skip_func", scope: !1, file: !1, line: 550, type: !101, isLocal: true, isDefinition: true, scopeLine: 559, flags: DIFlagPrototyped, isOptimized: false, variables: !67)
!101 = !DISubroutineType(types: !102)
!102 = !{null, !94, !94, !95, !11, !11, !98, !94, !94}
!103 = !{i32 2, !"Dwarf Version", i32 4}
!104 = !{i32 2, !"Debug Info Version", i32 3}
!105 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!106 = !DILocalVariable(name: "mf", arg: 1, scope: !19, file: !1, line: 22, type: !22)
!107 = !DIExpression()
!108 = !DILocation(line: 22, column: 23, scope: !19)
!109 = !DILocalVariable(name: "count_ptr", arg: 2, scope: !19, file: !1, line: 22, type: !55)
!110 = !DILocation(line: 22, column: 37, scope: !19)
!111 = !DILocalVariable(name: "matches", arg: 3, scope: !19, file: !1, line: 22, type: !44)
!112 = !DILocation(line: 22, column: 60, scope: !19)
!113 = !DILocalVariable(name: "count", scope: !19, file: !1, line: 27, type: !94)
!114 = !DILocation(line: 27, column: 17, scope: !19)
!115 = !DILocation(line: 27, column: 25, scope: !19)
!116 = !DILocation(line: 27, column: 29, scope: !19)
!117 = !DILocation(line: 27, column: 34, scope: !19)
!118 = !DILocation(line: 27, column: 38, scope: !19)
!119 = !DILocalVariable(name: "len_best", scope: !19, file: !1, line: 31, type: !11)
!120 = !DILocation(line: 31, column: 11, scope: !19)
!121 = !DILocation(line: 33, column: 6, scope: !122)
!122 = distinct !DILexicalBlock(scope: !19, file: !1, line: 33, column: 6)
!123 = !DILocation(line: 33, column: 12, scope: !122)
!124 = !DILocation(line: 33, column: 6, scope: !19)
!125 = !DILocalVariable(name: "i", scope: !126, file: !1, line: 35, type: !11)
!126 = distinct !DILexicalBlock(scope: !122, file: !1, line: 33, column: 17)
!127 = !DILocation(line: 35, column: 12, scope: !126)
!128 = !DILocation(line: 37, column: 10, scope: !129)
!129 = distinct !DILexicalBlock(scope: !126, file: !1, line: 37, column: 3)
!130 = !DILocation(line: 37, column: 8, scope: !129)
!131 = !DILocation(line: 37, column: 15, scope: !132)
!132 = !DILexicalBlockFile(scope: !133, file: !1, discriminator: 1)
!133 = distinct !DILexicalBlock(scope: !129, file: !1, line: 37, column: 3)
!134 = !DILocation(line: 37, column: 19, scope: !132)
!135 = !DILocation(line: 37, column: 17, scope: !132)
!136 = !DILocation(line: 37, column: 3, scope: !132)
!137 = !DILocation(line: 38, column: 4, scope: !138)
!138 = distinct !DILexicalBlock(scope: !133, file: !1, line: 37, column: 31)
!139 = !DILocation(line: 38, column: 4, scope: !140)
!140 = !DILexicalBlockFile(scope: !138, file: !1, discriminator: 1)
!141 = !DILocation(line: 38, column: 4, scope: !142)
!142 = !DILexicalBlockFile(scope: !138, file: !1, discriminator: 2)
!143 = !DILocation(line: 38, column: 4, scope: !144)
!144 = !DILexicalBlockFile(scope: !138, file: !1, discriminator: 3)
!145 = !DILocation(line: 39, column: 4, scope: !138)
!146 = !DILocation(line: 39, column: 4, scope: !140)
!147 = !DILocation(line: 39, column: 4, scope: !142)
!148 = !DILocation(line: 39, column: 4, scope: !144)
!149 = !DILocation(line: 40, column: 4, scope: !138)
!150 = !DILocation(line: 40, column: 4, scope: !151)
!151 = !DILexicalBlockFile(scope: !138, file: !1, discriminator: 4)
!152 = !DILocation(line: 40, column: 4, scope: !153)
!153 = !DILexicalBlockFile(scope: !138, file: !1, discriminator: 5)
!154 = !DILocation(line: 40, column: 4, scope: !140)
!155 = !DILocation(line: 40, column: 4, scope: !142)
!156 = !DILocation(line: 40, column: 4, scope: !144)
!157 = !DILocation(line: 43, column: 3, scope: !138)
!158 = !DILocation(line: 37, column: 26, scope: !159)
!159 = !DILexicalBlockFile(scope: !133, file: !1, discriminator: 2)
!160 = !DILocation(line: 37, column: 3, scope: !159)
!161 = !DILocation(line: 48, column: 22, scope: !126)
!162 = !DILocation(line: 48, column: 28, scope: !126)
!163 = !DILocation(line: 48, column: 14, scope: !126)
!164 = !DILocation(line: 48, column: 33, scope: !126)
!165 = !DILocation(line: 48, column: 12, scope: !126)
!166 = !DILocation(line: 52, column: 7, scope: !167)
!167 = distinct !DILexicalBlock(scope: !126, file: !1, line: 52, column: 7)
!168 = !DILocation(line: 52, column: 19, scope: !167)
!169 = !DILocation(line: 52, column: 23, scope: !167)
!170 = !DILocation(line: 52, column: 16, scope: !167)
!171 = !DILocation(line: 52, column: 7, scope: !126)
!172 = !DILocalVariable(name: "p1", scope: !173, file: !1, line: 53, type: !28)
!173 = distinct !DILexicalBlock(scope: !167, file: !1, line: 52, column: 33)
!174 = !DILocation(line: 53, column: 13, scope: !173)
!175 = !DILocalVariable(name: "p2", scope: !173, file: !1, line: 54, type: !28)
!176 = !DILocation(line: 54, column: 13, scope: !173)
!177 = !DILocalVariable(name: "limit", scope: !173, file: !1, line: 60, type: !11)
!178 = !DILocation(line: 60, column: 13, scope: !173)
!179 = !DILocation(line: 60, column: 30, scope: !173)
!180 = !DILocation(line: 60, column: 21, scope: !173)
!181 = !DILocation(line: 60, column: 34, scope: !173)
!182 = !DILocation(line: 61, column: 8, scope: !183)
!183 = distinct !DILexicalBlock(scope: !173, file: !1, line: 61, column: 8)
!184 = !DILocation(line: 61, column: 16, scope: !183)
!185 = !DILocation(line: 61, column: 20, scope: !183)
!186 = !DILocation(line: 61, column: 14, scope: !183)
!187 = !DILocation(line: 61, column: 8, scope: !173)
!188 = !DILocation(line: 62, column: 13, scope: !183)
!189 = !DILocation(line: 62, column: 17, scope: !183)
!190 = !DILocation(line: 62, column: 11, scope: !183)
!191 = !DILocation(line: 62, column: 5, scope: !183)
!192 = !DILocation(line: 66, column: 16, scope: !173)
!193 = !DILocation(line: 66, column: 9, scope: !173)
!194 = !DILocation(line: 66, column: 20, scope: !173)
!195 = !DILocation(line: 66, column: 7, scope: !173)
!196 = !DILocation(line: 70, column: 9, scope: !173)
!197 = !DILocation(line: 70, column: 22, scope: !173)
!198 = !DILocation(line: 70, column: 28, scope: !173)
!199 = !DILocation(line: 70, column: 14, scope: !173)
!200 = !DILocation(line: 70, column: 33, scope: !173)
!201 = !DILocation(line: 70, column: 12, scope: !173)
!202 = !DILocation(line: 70, column: 38, scope: !173)
!203 = !DILocation(line: 70, column: 7, scope: !173)
!204 = !DILocation(line: 72, column: 4, scope: !173)
!205 = !DILocation(line: 72, column: 11, scope: !206)
!206 = !DILexicalBlockFile(scope: !173, file: !1, discriminator: 1)
!207 = !DILocation(line: 72, column: 22, scope: !206)
!208 = !DILocation(line: 72, column: 20, scope: !206)
!209 = !DILocation(line: 73, column: 6, scope: !173)
!210 = !DILocation(line: 73, column: 12, scope: !206)
!211 = !DILocation(line: 73, column: 9, scope: !206)
!212 = !DILocation(line: 73, column: 28, scope: !206)
!213 = !DILocation(line: 73, column: 25, scope: !206)
!214 = !DILocation(line: 73, column: 22, scope: !206)
!215 = !DILocation(line: 72, column: 4, scope: !216)
!216 = !DILexicalBlockFile(scope: !173, file: !1, discriminator: 2)
!217 = !DILocation(line: 74, column: 5, scope: !173)
!218 = !DILocation(line: 72, column: 4, scope: !219)
!219 = !DILexicalBlockFile(scope: !173, file: !1, discriminator: 3)
!220 = !DILocation(line: 75, column: 3, scope: !173)
!221 = !DILocation(line: 76, column: 2, scope: !126)
!222 = !DILocation(line: 78, column: 15, scope: !19)
!223 = !DILocation(line: 78, column: 3, scope: !19)
!224 = !DILocation(line: 78, column: 13, scope: !19)
!225 = !DILocation(line: 82, column: 4, scope: !19)
!226 = !DILocation(line: 82, column: 8, scope: !19)
!227 = !DILocation(line: 82, column: 2, scope: !19)
!228 = !DILocation(line: 84, column: 9, scope: !19)
!229 = !DILocation(line: 84, column: 2, scope: !19)
!230 = !DILocalVariable(name: "mf", arg: 1, scope: !78, file: !24, line: 222, type: !81)
!231 = !DILocation(line: 222, column: 23, scope: !78)
!232 = !DILocation(line: 224, column: 9, scope: !78)
!233 = !DILocation(line: 224, column: 13, scope: !78)
!234 = !DILocation(line: 224, column: 22, scope: !78)
!235 = !DILocation(line: 224, column: 26, scope: !78)
!236 = !DILocation(line: 224, column: 20, scope: !78)
!237 = !DILocation(line: 224, column: 2, scope: !78)
!238 = !DILocalVariable(name: "mf", arg: 1, scope: !83, file: !24, line: 230, type: !81)
!239 = !DILocation(line: 230, column: 25, scope: !83)
!240 = !DILocation(line: 232, column: 9, scope: !83)
!241 = !DILocation(line: 232, column: 13, scope: !83)
!242 = !DILocation(line: 232, column: 25, scope: !83)
!243 = !DILocation(line: 232, column: 29, scope: !83)
!244 = !DILocation(line: 232, column: 23, scope: !83)
!245 = !DILocation(line: 232, column: 2, scope: !83)
!246 = !DILocalVariable(name: "mf", arg: 1, scope: !68, file: !1, line: 314, type: !22)
!247 = !DILocation(line: 314, column: 27, scope: !68)
!248 = !DILocalVariable(name: "matches", arg: 2, scope: !68, file: !1, line: 314, type: !44)
!249 = !DILocation(line: 314, column: 43, scope: !68)
!250 = !DILocalVariable(name: "cur", scope: !68, file: !1, line: 316, type: !96)
!251 = !DILocation(line: 316, column: 17, scope: !68)
!252 = !DILocalVariable(name: "pos", scope: !68, file: !1, line: 317, type: !11)
!253 = !DILocation(line: 317, column: 11, scope: !68)
!254 = !DILocalVariable(name: "temp", scope: !68, file: !1, line: 318, type: !11)
!255 = !DILocation(line: 318, column: 11, scope: !68)
!256 = !DILocalVariable(name: "hash_value", scope: !68, file: !1, line: 318, type: !11)
!257 = !DILocation(line: 318, column: 17, scope: !68)
!258 = !DILocalVariable(name: "hash_2_value", scope: !68, file: !1, line: 318, type: !11)
!259 = !DILocation(line: 318, column: 29, scope: !68)
!260 = !DILocalVariable(name: "delta2", scope: !68, file: !1, line: 319, type: !11)
!261 = !DILocation(line: 319, column: 11, scope: !68)
!262 = !DILocalVariable(name: "cur_match", scope: !68, file: !1, line: 319, type: !11)
!263 = !DILocation(line: 319, column: 19, scope: !68)
!264 = !DILocalVariable(name: "len_best", scope: !68, file: !1, line: 320, type: !11)
!265 = !DILocation(line: 320, column: 11, scope: !68)
!266 = !DILocalVariable(name: "matches_count", scope: !68, file: !1, line: 321, type: !11)
!267 = !DILocation(line: 321, column: 11, scope: !68)
!268 = !DILocalVariable(name: "len_limit", scope: !68, file: !1, line: 323, type: !11)
!269 = !DILocation(line: 323, column: 2, scope: !68)
!270 = !DILocation(line: 323, column: 2, scope: !271)
!271 = distinct !DILexicalBlock(scope: !68, file: !1, line: 323, column: 2)
!272 = !DILocation(line: 323, column: 2, scope: !273)
!273 = !DILexicalBlockFile(scope: !274, file: !1, discriminator: 1)
!274 = distinct !DILexicalBlock(scope: !271, file: !1, line: 323, column: 2)
!275 = !DILocation(line: 323, column: 2, scope: !276)
!276 = !DILexicalBlockFile(scope: !277, file: !1, discriminator: 2)
!277 = distinct !DILexicalBlock(scope: !271, file: !1, line: 323, column: 2)
!278 = !DILocation(line: 323, column: 2, scope: !279)
!279 = !DILexicalBlockFile(scope: !280, file: !1, discriminator: 3)
!280 = distinct !DILexicalBlock(scope: !277, file: !1, line: 323, column: 2)
!281 = !DILocation(line: 323, column: 2, scope: !282)
!282 = !DILexicalBlockFile(scope: !280, file: !1, discriminator: 4)
!283 = !DILocation(line: 323, column: 2, scope: !284)
!284 = !DILexicalBlockFile(scope: !280, file: !1, discriminator: 5)
!285 = !DILocation(line: 323, column: 2, scope: !286)
!286 = !DILexicalBlockFile(scope: !280, file: !1, discriminator: 6)
!287 = !DILocation(line: 323, column: 2, scope: !288)
!288 = !DILexicalBlockFile(scope: !280, file: !1, discriminator: 7)
!289 = !DILocation(line: 323, column: 2, scope: !290)
!290 = !DILexicalBlockFile(scope: !68, file: !1, discriminator: 8)
!291 = !DILocation(line: 325, column: 2, scope: !68)
!292 = !DILocation(line: 327, column: 11, scope: !68)
!293 = !DILocation(line: 327, column: 26, scope: !68)
!294 = !DILocation(line: 327, column: 17, scope: !68)
!295 = !DILocation(line: 327, column: 21, scope: !68)
!296 = !DILocation(line: 327, column: 15, scope: !68)
!297 = !DILocation(line: 327, column: 9, scope: !68)
!298 = !DILocation(line: 328, column: 41, scope: !68)
!299 = !DILocation(line: 328, column: 39, scope: !68)
!300 = !DILocation(line: 328, column: 14, scope: !68)
!301 = !DILocation(line: 328, column: 18, scope: !68)
!302 = !DILocation(line: 328, column: 12, scope: !68)
!303 = !DILocation(line: 330, column: 27, scope: !68)
!304 = !DILocation(line: 330, column: 11, scope: !68)
!305 = !DILocation(line: 330, column: 2, scope: !68)
!306 = !DILocation(line: 330, column: 6, scope: !68)
!307 = !DILocation(line: 330, column: 25, scope: !68)
!308 = !DILocation(line: 331, column: 43, scope: !68)
!309 = !DILocation(line: 331, column: 29, scope: !68)
!310 = !DILocation(line: 331, column: 27, scope: !68)
!311 = !DILocation(line: 331, column: 2, scope: !68)
!312 = !DILocation(line: 331, column: 6, scope: !68)
!313 = !DILocation(line: 331, column: 41, scope: !68)
!314 = !DILocation(line: 333, column: 6, scope: !315)
!315 = distinct !DILexicalBlock(scope: !68, file: !1, line: 333, column: 6)
!316 = !DILocation(line: 333, column: 15, scope: !315)
!317 = !DILocation(line: 333, column: 19, scope: !315)
!318 = !DILocation(line: 333, column: 13, scope: !315)
!319 = !DILocation(line: 333, column: 31, scope: !315)
!320 = !DILocation(line: 333, column: 36, scope: !321)
!321 = !DILexicalBlockFile(scope: !315, file: !1, discriminator: 1)
!322 = !DILocation(line: 333, column: 42, scope: !321)
!323 = !DILocation(line: 333, column: 40, scope: !321)
!324 = !DILocation(line: 333, column: 34, scope: !321)
!325 = !DILocation(line: 333, column: 54, scope: !321)
!326 = !DILocation(line: 333, column: 53, scope: !321)
!327 = !DILocation(line: 333, column: 50, scope: !321)
!328 = !DILocation(line: 333, column: 6, scope: !321)
!329 = !DILocation(line: 334, column: 3, scope: !330)
!330 = distinct !DILexicalBlock(scope: !315, file: !1, line: 333, column: 59)
!331 = !DILocation(line: 334, column: 11, scope: !332)
!332 = !DILexicalBlockFile(scope: !333, file: !1, discriminator: 1)
!333 = distinct !DILexicalBlock(scope: !334, file: !1, line: 334, column: 3)
!334 = distinct !DILexicalBlock(scope: !330, file: !1, line: 334, column: 3)
!335 = !DILocation(line: 334, column: 23, scope: !332)
!336 = !DILocation(line: 334, column: 20, scope: !332)
!337 = !DILocation(line: 334, column: 3, scope: !332)
!338 = !DILocation(line: 335, column: 10, scope: !339)
!339 = distinct !DILexicalBlock(scope: !333, file: !1, line: 335, column: 8)
!340 = !DILocation(line: 335, column: 16, scope: !339)
!341 = !DILocation(line: 335, column: 14, scope: !339)
!342 = !DILocation(line: 335, column: 27, scope: !339)
!343 = !DILocation(line: 335, column: 25, scope: !339)
!344 = !DILocation(line: 335, column: 8, scope: !339)
!345 = !DILocation(line: 335, column: 42, scope: !339)
!346 = !DILocation(line: 335, column: 38, scope: !339)
!347 = !DILocation(line: 335, column: 35, scope: !339)
!348 = !DILocation(line: 335, column: 8, scope: !333)
!349 = !DILocation(line: 336, column: 5, scope: !339)
!350 = !DILocation(line: 335, column: 50, scope: !351)
!351 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 1)
!352 = !DILocation(line: 334, column: 34, scope: !353)
!353 = !DILexicalBlockFile(scope: !333, file: !1, discriminator: 2)
!354 = !DILocation(line: 334, column: 3, scope: !353)
!355 = !DILocation(line: 338, column: 20, scope: !330)
!356 = !DILocation(line: 338, column: 3, scope: !330)
!357 = !DILocation(line: 338, column: 14, scope: !330)
!358 = !DILocation(line: 338, column: 18, scope: !330)
!359 = !DILocation(line: 339, column: 21, scope: !330)
!360 = !DILocation(line: 339, column: 28, scope: !330)
!361 = !DILocation(line: 339, column: 3, scope: !330)
!362 = !DILocation(line: 339, column: 14, scope: !330)
!363 = !DILocation(line: 339, column: 19, scope: !330)
!364 = !DILocation(line: 340, column: 17, scope: !330)
!365 = !DILocation(line: 342, column: 7, scope: !366)
!366 = distinct !DILexicalBlock(scope: !330, file: !1, line: 342, column: 7)
!367 = !DILocation(line: 342, column: 19, scope: !366)
!368 = !DILocation(line: 342, column: 16, scope: !366)
!369 = !DILocation(line: 342, column: 7, scope: !330)
!370 = !DILocation(line: 343, column: 4, scope: !371)
!371 = distinct !DILexicalBlock(scope: !366, file: !1, line: 342, column: 30)
!372 = !DILocation(line: 343, column: 4, scope: !373)
!373 = !DILexicalBlockFile(scope: !374, file: !1, discriminator: 1)
!374 = distinct !DILexicalBlock(scope: !371, file: !1, line: 343, column: 4)
!375 = !DILocation(line: 344, column: 4, scope: !371)
!376 = !DILocation(line: 346, column: 2, scope: !330)
!377 = !DILocation(line: 348, column: 2, scope: !68)
!378 = !DILocation(line: 348, column: 2, scope: !379)
!379 = !DILexicalBlockFile(scope: !380, file: !1, discriminator: 1)
!380 = distinct !DILexicalBlock(scope: !68, file: !1, line: 348, column: 2)
!381 = !DILocation(line: 348, column: 2, scope: !382)
!382 = !DILexicalBlockFile(scope: !379, file: !1, discriminator: 2)
!383 = !DILocation(line: 349, column: 1, scope: !68)
!384 = !DILocalVariable(name: "mf", arg: 1, scope: !86, file: !1, line: 184, type: !22)
!385 = !DILocation(line: 184, column: 23, scope: !86)
!386 = !DILocation(line: 186, column: 4, scope: !86)
!387 = !DILocation(line: 186, column: 8, scope: !86)
!388 = !DILocation(line: 186, column: 2, scope: !86)
!389 = !DILocation(line: 187, column: 2, scope: !86)
!390 = !DILocation(line: 187, column: 2, scope: !391)
!391 = !DILexicalBlockFile(scope: !86, file: !1, discriminator: 1)
!392 = !DILocation(line: 187, column: 2, scope: !393)
!393 = !DILexicalBlockFile(scope: !86, file: !1, discriminator: 2)
!394 = !DILocation(line: 187, column: 2, scope: !395)
!395 = !DILexicalBlockFile(scope: !86, file: !1, discriminator: 3)
!396 = !DILocation(line: 188, column: 4, scope: !86)
!397 = !DILocation(line: 188, column: 8, scope: !86)
!398 = !DILocation(line: 188, column: 2, scope: !86)
!399 = !DILocation(line: 189, column: 1, scope: !86)
!400 = !DILocalVariable(name: "mf", arg: 1, scope: !89, file: !1, line: 156, type: !22)
!401 = !DILocation(line: 156, column: 19, scope: !89)
!402 = !DILocation(line: 158, column: 8, scope: !403)
!403 = distinct !DILexicalBlock(scope: !89, file: !1, line: 158, column: 6)
!404 = !DILocation(line: 158, column: 12, scope: !403)
!405 = !DILocation(line: 158, column: 6, scope: !403)
!406 = !DILocation(line: 158, column: 26, scope: !403)
!407 = !DILocation(line: 158, column: 30, scope: !403)
!408 = !DILocation(line: 158, column: 23, scope: !403)
!409 = !DILocation(line: 158, column: 6, scope: !89)
!410 = !DILocation(line: 159, column: 3, scope: !403)
!411 = !DILocation(line: 159, column: 7, scope: !403)
!412 = !DILocation(line: 159, column: 18, scope: !403)
!413 = !DILocation(line: 161, column: 4, scope: !89)
!414 = !DILocation(line: 161, column: 8, scope: !89)
!415 = !DILocation(line: 161, column: 2, scope: !89)
!416 = !DILocation(line: 162, column: 2, scope: !89)
!417 = !DILocation(line: 162, column: 2, scope: !418)
!418 = !DILexicalBlockFile(scope: !89, file: !1, discriminator: 1)
!419 = !DILocation(line: 162, column: 2, scope: !420)
!420 = !DILexicalBlockFile(scope: !89, file: !1, discriminator: 2)
!421 = !DILocation(line: 162, column: 2, scope: !422)
!422 = !DILexicalBlockFile(scope: !89, file: !1, discriminator: 3)
!423 = !DILocation(line: 164, column: 6, scope: !424)
!424 = distinct !DILexicalBlock(scope: !89, file: !1, line: 164, column: 6)
!425 = !DILocation(line: 164, column: 6, scope: !89)
!426 = !DILocation(line: 165, column: 13, scope: !424)
!427 = !DILocation(line: 165, column: 3, scope: !424)
!428 = !DILocation(line: 166, column: 1, scope: !89)
!429 = !DILocalVariable(name: "len_limit", arg: 1, scope: !91, file: !1, line: 256, type: !94)
!430 = !DILocation(line: 256, column: 18, scope: !91)
!431 = !DILocalVariable(name: "pos", arg: 2, scope: !91, file: !1, line: 257, type: !94)
!432 = !DILocation(line: 257, column: 18, scope: !91)
!433 = !DILocalVariable(name: "cur", arg: 3, scope: !91, file: !1, line: 258, type: !95)
!434 = !DILocation(line: 258, column: 24, scope: !91)
!435 = !DILocalVariable(name: "cur_match", arg: 4, scope: !91, file: !1, line: 259, type: !11)
!436 = !DILocation(line: 259, column: 12, scope: !91)
!437 = !DILocalVariable(name: "depth", arg: 5, scope: !91, file: !1, line: 260, type: !11)
!438 = !DILocation(line: 260, column: 12, scope: !91)
!439 = !DILocalVariable(name: "son", arg: 6, scope: !91, file: !1, line: 261, type: !98)
!440 = !DILocation(line: 261, column: 19, scope: !91)
!441 = !DILocalVariable(name: "cyclic_pos", arg: 7, scope: !91, file: !1, line: 262, type: !94)
!442 = !DILocation(line: 262, column: 18, scope: !91)
!443 = !DILocalVariable(name: "cyclic_size", arg: 8, scope: !91, file: !1, line: 263, type: !94)
!444 = !DILocation(line: 263, column: 18, scope: !91)
!445 = !DILocalVariable(name: "matches", arg: 9, scope: !91, file: !1, line: 264, type: !44)
!446 = !DILocation(line: 264, column: 15, scope: !91)
!447 = !DILocalVariable(name: "len_best", arg: 10, scope: !91, file: !1, line: 265, type: !11)
!448 = !DILocation(line: 265, column: 12, scope: !91)
!449 = !DILocation(line: 267, column: 20, scope: !91)
!450 = !DILocation(line: 267, column: 6, scope: !91)
!451 = !DILocation(line: 267, column: 2, scope: !91)
!452 = !DILocation(line: 267, column: 18, scope: !91)
!453 = !DILocation(line: 269, column: 2, scope: !91)
!454 = !DILocalVariable(name: "delta", scope: !455, file: !1, line: 270, type: !94)
!455 = distinct !DILexicalBlock(scope: !91, file: !1, line: 269, column: 15)
!456 = !DILocation(line: 270, column: 18, scope: !455)
!457 = !DILocation(line: 270, column: 26, scope: !455)
!458 = !DILocation(line: 270, column: 32, scope: !455)
!459 = !DILocation(line: 270, column: 30, scope: !455)
!460 = !DILocalVariable(name: "pb", scope: !455, file: !1, line: 271, type: !96)
!461 = !DILocation(line: 271, column: 18, scope: !455)
!462 = !DILocation(line: 272, column: 12, scope: !463)
!463 = distinct !DILexicalBlock(scope: !455, file: !1, line: 272, column: 7)
!464 = !DILocation(line: 272, column: 15, scope: !463)
!465 = !DILocation(line: 272, column: 20, scope: !463)
!466 = !DILocation(line: 272, column: 23, scope: !467)
!467 = !DILexicalBlockFile(scope: !463, file: !1, discriminator: 1)
!468 = !DILocation(line: 272, column: 32, scope: !467)
!469 = !DILocation(line: 272, column: 29, scope: !467)
!470 = !DILocation(line: 272, column: 7, scope: !467)
!471 = !DILocation(line: 273, column: 11, scope: !463)
!472 = !DILocation(line: 273, column: 4, scope: !463)
!473 = !DILocation(line: 275, column: 8, scope: !455)
!474 = !DILocation(line: 275, column: 14, scope: !455)
!475 = !DILocation(line: 275, column: 12, scope: !455)
!476 = !DILocation(line: 275, column: 6, scope: !455)
!477 = !DILocation(line: 276, column: 19, scope: !455)
!478 = !DILocation(line: 276, column: 32, scope: !455)
!479 = !DILocation(line: 276, column: 30, scope: !455)
!480 = !DILocation(line: 277, column: 8, scope: !455)
!481 = !DILocation(line: 277, column: 16, scope: !455)
!482 = !DILocation(line: 277, column: 14, scope: !455)
!483 = !DILocation(line: 277, column: 29, scope: !484)
!484 = !DILexicalBlockFile(scope: !455, file: !1, discriminator: 1)
!485 = !DILocation(line: 277, column: 8, scope: !484)
!486 = !DILocation(line: 277, column: 8, scope: !487)
!487 = !DILexicalBlockFile(scope: !455, file: !1, discriminator: 2)
!488 = !DILocation(line: 277, column: 8, scope: !489)
!489 = !DILexicalBlockFile(scope: !455, file: !1, discriminator: 3)
!490 = !DILocation(line: 277, column: 5, scope: !489)
!491 = !DILocation(line: 276, column: 15, scope: !484)
!492 = !DILocation(line: 276, column: 13, scope: !484)
!493 = !DILocation(line: 279, column: 10, scope: !494)
!494 = distinct !DILexicalBlock(scope: !455, file: !1, line: 279, column: 7)
!495 = !DILocation(line: 279, column: 7, scope: !494)
!496 = !DILocation(line: 279, column: 27, scope: !494)
!497 = !DILocation(line: 279, column: 23, scope: !494)
!498 = !DILocation(line: 279, column: 20, scope: !494)
!499 = !DILocation(line: 279, column: 37, scope: !494)
!500 = !DILocation(line: 279, column: 40, scope: !501)
!501 = !DILexicalBlockFile(scope: !494, file: !1, discriminator: 1)
!502 = !DILocation(line: 279, column: 49, scope: !501)
!503 = !DILocation(line: 279, column: 46, scope: !501)
!504 = !DILocation(line: 279, column: 7, scope: !501)
!505 = !DILocalVariable(name: "len", scope: !506, file: !1, line: 280, type: !11)
!506 = distinct !DILexicalBlock(scope: !494, file: !1, line: 279, column: 57)
!507 = !DILocation(line: 280, column: 13, scope: !506)
!508 = !DILocation(line: 281, column: 4, scope: !506)
!509 = !DILocation(line: 281, column: 11, scope: !510)
!510 = !DILexicalBlockFile(scope: !506, file: !1, discriminator: 1)
!511 = !DILocation(line: 281, column: 20, scope: !510)
!512 = !DILocation(line: 281, column: 17, scope: !510)
!513 = !DILocation(line: 281, column: 4, scope: !510)
!514 = !DILocation(line: 282, column: 12, scope: !515)
!515 = distinct !DILexicalBlock(scope: !506, file: !1, line: 282, column: 9)
!516 = !DILocation(line: 282, column: 9, scope: !515)
!517 = !DILocation(line: 282, column: 24, scope: !515)
!518 = !DILocation(line: 282, column: 20, scope: !515)
!519 = !DILocation(line: 282, column: 17, scope: !515)
!520 = !DILocation(line: 282, column: 9, scope: !506)
!521 = !DILocation(line: 283, column: 6, scope: !515)
!522 = !DILocation(line: 281, column: 4, scope: !523)
!523 = !DILexicalBlockFile(scope: !506, file: !1, discriminator: 2)
!524 = !DILocation(line: 285, column: 8, scope: !525)
!525 = distinct !DILexicalBlock(scope: !506, file: !1, line: 285, column: 8)
!526 = !DILocation(line: 285, column: 19, scope: !525)
!527 = !DILocation(line: 285, column: 17, scope: !525)
!528 = !DILocation(line: 285, column: 8, scope: !506)
!529 = !DILocation(line: 286, column: 16, scope: !530)
!530 = distinct !DILexicalBlock(scope: !525, file: !1, line: 285, column: 24)
!531 = !DILocation(line: 286, column: 14, scope: !530)
!532 = !DILocation(line: 287, column: 20, scope: !530)
!533 = !DILocation(line: 287, column: 5, scope: !530)
!534 = !DILocation(line: 287, column: 14, scope: !530)
!535 = !DILocation(line: 287, column: 18, scope: !530)
!536 = !DILocation(line: 288, column: 21, scope: !530)
!537 = !DILocation(line: 288, column: 27, scope: !530)
!538 = !DILocation(line: 288, column: 5, scope: !530)
!539 = !DILocation(line: 288, column: 14, scope: !530)
!540 = !DILocation(line: 288, column: 19, scope: !530)
!541 = !DILocation(line: 289, column: 5, scope: !530)
!542 = !DILocation(line: 291, column: 9, scope: !543)
!543 = distinct !DILexicalBlock(scope: !530, file: !1, line: 291, column: 9)
!544 = !DILocation(line: 291, column: 16, scope: !543)
!545 = !DILocation(line: 291, column: 13, scope: !543)
!546 = !DILocation(line: 291, column: 9, scope: !530)
!547 = !DILocation(line: 292, column: 13, scope: !543)
!548 = !DILocation(line: 292, column: 6, scope: !543)
!549 = !DILocation(line: 293, column: 4, scope: !530)
!550 = !DILocation(line: 294, column: 3, scope: !506)
!551 = !DILocation(line: 269, column: 2, scope: !552)
!552 = !DILexicalBlockFile(scope: !91, file: !1, discriminator: 1)
!553 = !DILocation(line: 296, column: 1, scope: !91)
!554 = !DILocalVariable(name: "mf", arg: 1, scope: !69, file: !1, line: 353, type: !22)
!555 = !DILocation(line: 353, column: 27, scope: !69)
!556 = !DILocalVariable(name: "amount", arg: 2, scope: !69, file: !1, line: 353, type: !11)
!557 = !DILocation(line: 353, column: 40, scope: !69)
!558 = !DILocation(line: 355, column: 2, scope: !69)
!559 = !DILocalVariable(name: "cur", scope: !560, file: !1, line: 356, type: !96)
!560 = distinct !DILexicalBlock(scope: !69, file: !1, line: 355, column: 5)
!561 = !DILocation(line: 356, column: 18, scope: !560)
!562 = !DILocalVariable(name: "pos", scope: !560, file: !1, line: 357, type: !11)
!563 = !DILocation(line: 357, column: 12, scope: !560)
!564 = !DILocalVariable(name: "temp", scope: !560, file: !1, line: 358, type: !11)
!565 = !DILocation(line: 358, column: 12, scope: !560)
!566 = !DILocalVariable(name: "hash_value", scope: !560, file: !1, line: 358, type: !11)
!567 = !DILocation(line: 358, column: 18, scope: !560)
!568 = !DILocalVariable(name: "hash_2_value", scope: !560, file: !1, line: 358, type: !11)
!569 = !DILocation(line: 358, column: 30, scope: !560)
!570 = !DILocalVariable(name: "cur_match", scope: !560, file: !1, line: 359, type: !11)
!571 = !DILocation(line: 359, column: 12, scope: !560)
!572 = !DILocation(line: 361, column: 16, scope: !573)
!573 = distinct !DILexicalBlock(scope: !560, file: !1, line: 361, column: 7)
!574 = !DILocation(line: 361, column: 7, scope: !573)
!575 = !DILocation(line: 361, column: 20, scope: !573)
!576 = !DILocation(line: 361, column: 7, scope: !560)
!577 = !DILocation(line: 362, column: 17, scope: !578)
!578 = distinct !DILexicalBlock(scope: !573, file: !1, line: 361, column: 25)
!579 = !DILocation(line: 362, column: 4, scope: !578)
!580 = !DILocation(line: 363, column: 4, scope: !578)
!581 = !DILocation(line: 366, column: 16, scope: !560)
!582 = !DILocation(line: 366, column: 9, scope: !560)
!583 = !DILocation(line: 366, column: 7, scope: !560)
!584 = !DILocation(line: 367, column: 9, scope: !560)
!585 = !DILocation(line: 367, column: 13, scope: !560)
!586 = !DILocation(line: 367, column: 24, scope: !560)
!587 = !DILocation(line: 367, column: 28, scope: !560)
!588 = !DILocation(line: 367, column: 22, scope: !560)
!589 = !DILocation(line: 367, column: 7, scope: !560)
!590 = !DILocation(line: 369, column: 3, scope: !560)
!591 = !DILocation(line: 371, column: 42, scope: !560)
!592 = !DILocation(line: 371, column: 40, scope: !560)
!593 = !DILocation(line: 371, column: 15, scope: !560)
!594 = !DILocation(line: 371, column: 19, scope: !560)
!595 = !DILocation(line: 371, column: 13, scope: !560)
!596 = !DILocation(line: 373, column: 28, scope: !560)
!597 = !DILocation(line: 373, column: 12, scope: !560)
!598 = !DILocation(line: 373, column: 3, scope: !560)
!599 = !DILocation(line: 373, column: 7, scope: !560)
!600 = !DILocation(line: 373, column: 26, scope: !560)
!601 = !DILocation(line: 374, column: 44, scope: !560)
!602 = !DILocation(line: 374, column: 30, scope: !560)
!603 = !DILocation(line: 374, column: 28, scope: !560)
!604 = !DILocation(line: 374, column: 3, scope: !560)
!605 = !DILocation(line: 374, column: 7, scope: !560)
!606 = !DILocation(line: 374, column: 42, scope: !560)
!607 = !DILocation(line: 376, column: 3, scope: !560)
!608 = !DILocation(line: 376, column: 3, scope: !609)
!609 = !DILexicalBlockFile(scope: !610, file: !1, discriminator: 1)
!610 = distinct !DILexicalBlock(scope: !560, file: !1, line: 376, column: 3)
!611 = !DILocation(line: 378, column: 2, scope: !560)
!612 = !DILocation(line: 378, column: 11, scope: !613)
!613 = !DILexicalBlockFile(scope: !69, file: !1, discriminator: 1)
!614 = !DILocation(line: 378, column: 20, scope: !613)
!615 = !DILocation(line: 378, column: 2, scope: !613)
!616 = !DILocation(line: 379, column: 1, scope: !69)
!617 = !DILocalVariable(name: "mf", arg: 1, scope: !70, file: !1, line: 385, type: !22)
!618 = !DILocation(line: 385, column: 27, scope: !70)
!619 = !DILocalVariable(name: "matches", arg: 2, scope: !70, file: !1, line: 385, type: !44)
!620 = !DILocation(line: 385, column: 43, scope: !70)
!621 = !DILocalVariable(name: "cur", scope: !70, file: !1, line: 387, type: !96)
!622 = !DILocation(line: 387, column: 17, scope: !70)
!623 = !DILocalVariable(name: "pos", scope: !70, file: !1, line: 388, type: !11)
!624 = !DILocation(line: 388, column: 11, scope: !70)
!625 = !DILocalVariable(name: "temp", scope: !70, file: !1, line: 389, type: !11)
!626 = !DILocation(line: 389, column: 11, scope: !70)
!627 = !DILocalVariable(name: "hash_value", scope: !70, file: !1, line: 389, type: !11)
!628 = !DILocation(line: 389, column: 17, scope: !70)
!629 = !DILocalVariable(name: "hash_2_value", scope: !70, file: !1, line: 389, type: !11)
!630 = !DILocation(line: 389, column: 29, scope: !70)
!631 = !DILocalVariable(name: "hash_3_value", scope: !70, file: !1, line: 389, type: !11)
!632 = !DILocation(line: 389, column: 43, scope: !70)
!633 = !DILocalVariable(name: "delta2", scope: !70, file: !1, line: 390, type: !11)
!634 = !DILocation(line: 390, column: 11, scope: !70)
!635 = !DILocalVariable(name: "delta3", scope: !70, file: !1, line: 390, type: !11)
!636 = !DILocation(line: 390, column: 19, scope: !70)
!637 = !DILocalVariable(name: "cur_match", scope: !70, file: !1, line: 390, type: !11)
!638 = !DILocation(line: 390, column: 27, scope: !70)
!639 = !DILocalVariable(name: "len_best", scope: !70, file: !1, line: 391, type: !11)
!640 = !DILocation(line: 391, column: 11, scope: !70)
!641 = !DILocalVariable(name: "matches_count", scope: !70, file: !1, line: 392, type: !11)
!642 = !DILocation(line: 392, column: 11, scope: !70)
!643 = !DILocalVariable(name: "len_limit", scope: !70, file: !1, line: 394, type: !11)
!644 = !DILocation(line: 394, column: 2, scope: !70)
!645 = !DILocation(line: 394, column: 2, scope: !646)
!646 = distinct !DILexicalBlock(scope: !70, file: !1, line: 394, column: 2)
!647 = !DILocation(line: 394, column: 2, scope: !648)
!648 = !DILexicalBlockFile(scope: !649, file: !1, discriminator: 1)
!649 = distinct !DILexicalBlock(scope: !646, file: !1, line: 394, column: 2)
!650 = !DILocation(line: 394, column: 2, scope: !651)
!651 = !DILexicalBlockFile(scope: !652, file: !1, discriminator: 2)
!652 = distinct !DILexicalBlock(scope: !646, file: !1, line: 394, column: 2)
!653 = !DILocation(line: 394, column: 2, scope: !654)
!654 = !DILexicalBlockFile(scope: !655, file: !1, discriminator: 3)
!655 = distinct !DILexicalBlock(scope: !652, file: !1, line: 394, column: 2)
!656 = !DILocation(line: 394, column: 2, scope: !657)
!657 = !DILexicalBlockFile(scope: !655, file: !1, discriminator: 4)
!658 = !DILocation(line: 394, column: 2, scope: !659)
!659 = !DILexicalBlockFile(scope: !655, file: !1, discriminator: 5)
!660 = !DILocation(line: 394, column: 2, scope: !661)
!661 = !DILexicalBlockFile(scope: !655, file: !1, discriminator: 6)
!662 = !DILocation(line: 394, column: 2, scope: !663)
!663 = !DILexicalBlockFile(scope: !655, file: !1, discriminator: 7)
!664 = !DILocation(line: 394, column: 2, scope: !665)
!665 = !DILexicalBlockFile(scope: !70, file: !1, discriminator: 8)
!666 = !DILocation(line: 396, column: 2, scope: !70)
!667 = !DILocation(line: 398, column: 11, scope: !70)
!668 = !DILocation(line: 398, column: 26, scope: !70)
!669 = !DILocation(line: 398, column: 17, scope: !70)
!670 = !DILocation(line: 398, column: 21, scope: !70)
!671 = !DILocation(line: 398, column: 15, scope: !70)
!672 = !DILocation(line: 398, column: 9, scope: !70)
!673 = !DILocation(line: 399, column: 11, scope: !70)
!674 = !DILocation(line: 399, column: 44, scope: !70)
!675 = !DILocation(line: 399, column: 42, scope: !70)
!676 = !DILocation(line: 399, column: 17, scope: !70)
!677 = !DILocation(line: 399, column: 21, scope: !70)
!678 = !DILocation(line: 399, column: 15, scope: !70)
!679 = !DILocation(line: 399, column: 9, scope: !70)
!680 = !DILocation(line: 400, column: 41, scope: !70)
!681 = !DILocation(line: 400, column: 39, scope: !70)
!682 = !DILocation(line: 400, column: 14, scope: !70)
!683 = !DILocation(line: 400, column: 18, scope: !70)
!684 = !DILocation(line: 400, column: 12, scope: !70)
!685 = !DILocation(line: 402, column: 28, scope: !70)
!686 = !DILocation(line: 402, column: 11, scope: !70)
!687 = !DILocation(line: 402, column: 2, scope: !70)
!688 = !DILocation(line: 402, column: 6, scope: !70)
!689 = !DILocation(line: 402, column: 26, scope: !70)
!690 = !DILocation(line: 403, column: 45, scope: !70)
!691 = !DILocation(line: 403, column: 29, scope: !70)
!692 = !DILocation(line: 403, column: 27, scope: !70)
!693 = !DILocation(line: 403, column: 2, scope: !70)
!694 = !DILocation(line: 403, column: 6, scope: !70)
!695 = !DILocation(line: 403, column: 43, scope: !70)
!696 = !DILocation(line: 404, column: 43, scope: !70)
!697 = !DILocation(line: 404, column: 29, scope: !70)
!698 = !DILocation(line: 404, column: 27, scope: !70)
!699 = !DILocation(line: 404, column: 2, scope: !70)
!700 = !DILocation(line: 404, column: 6, scope: !70)
!701 = !DILocation(line: 404, column: 41, scope: !70)
!702 = !DILocation(line: 406, column: 6, scope: !703)
!703 = distinct !DILexicalBlock(scope: !70, file: !1, line: 406, column: 6)
!704 = !DILocation(line: 406, column: 15, scope: !703)
!705 = !DILocation(line: 406, column: 19, scope: !703)
!706 = !DILocation(line: 406, column: 13, scope: !703)
!707 = !DILocation(line: 406, column: 31, scope: !703)
!708 = !DILocation(line: 406, column: 36, scope: !709)
!709 = !DILexicalBlockFile(scope: !703, file: !1, discriminator: 1)
!710 = !DILocation(line: 406, column: 42, scope: !709)
!711 = !DILocation(line: 406, column: 40, scope: !709)
!712 = !DILocation(line: 406, column: 34, scope: !709)
!713 = !DILocation(line: 406, column: 54, scope: !709)
!714 = !DILocation(line: 406, column: 53, scope: !709)
!715 = !DILocation(line: 406, column: 50, scope: !709)
!716 = !DILocation(line: 406, column: 6, scope: !709)
!717 = !DILocation(line: 407, column: 12, scope: !718)
!718 = distinct !DILexicalBlock(scope: !703, file: !1, line: 406, column: 59)
!719 = !DILocation(line: 408, column: 3, scope: !718)
!720 = !DILocation(line: 408, column: 14, scope: !718)
!721 = !DILocation(line: 408, column: 18, scope: !718)
!722 = !DILocation(line: 409, column: 21, scope: !718)
!723 = !DILocation(line: 409, column: 28, scope: !718)
!724 = !DILocation(line: 409, column: 3, scope: !718)
!725 = !DILocation(line: 409, column: 14, scope: !718)
!726 = !DILocation(line: 409, column: 19, scope: !718)
!727 = !DILocation(line: 410, column: 17, scope: !718)
!728 = !DILocation(line: 411, column: 2, scope: !718)
!729 = !DILocation(line: 413, column: 6, scope: !730)
!730 = distinct !DILexicalBlock(scope: !70, file: !1, line: 413, column: 6)
!731 = !DILocation(line: 413, column: 16, scope: !730)
!732 = !DILocation(line: 413, column: 13, scope: !730)
!733 = !DILocation(line: 413, column: 23, scope: !730)
!734 = !DILocation(line: 413, column: 26, scope: !735)
!735 = !DILexicalBlockFile(scope: !730, file: !1, discriminator: 1)
!736 = !DILocation(line: 413, column: 35, scope: !735)
!737 = !DILocation(line: 413, column: 39, scope: !735)
!738 = !DILocation(line: 413, column: 33, scope: !735)
!739 = !DILocation(line: 414, column: 4, scope: !730)
!740 = !DILocation(line: 414, column: 9, scope: !735)
!741 = !DILocation(line: 414, column: 15, scope: !735)
!742 = !DILocation(line: 414, column: 13, scope: !735)
!743 = !DILocation(line: 414, column: 7, scope: !735)
!744 = !DILocation(line: 414, column: 27, scope: !735)
!745 = !DILocation(line: 414, column: 26, scope: !735)
!746 = !DILocation(line: 414, column: 23, scope: !735)
!747 = !DILocation(line: 413, column: 6, scope: !748)
!748 = !DILexicalBlockFile(scope: !70, file: !1, discriminator: 2)
!749 = !DILocation(line: 415, column: 12, scope: !750)
!750 = distinct !DILexicalBlock(scope: !730, file: !1, line: 414, column: 32)
!751 = !DILocation(line: 416, column: 35, scope: !750)
!752 = !DILocation(line: 416, column: 42, scope: !750)
!753 = !DILocation(line: 416, column: 24, scope: !750)
!754 = !DILocation(line: 416, column: 3, scope: !750)
!755 = !DILocation(line: 416, column: 28, scope: !750)
!756 = !DILocation(line: 416, column: 33, scope: !750)
!757 = !DILocation(line: 417, column: 12, scope: !750)
!758 = !DILocation(line: 417, column: 10, scope: !750)
!759 = !DILocation(line: 418, column: 2, scope: !750)
!760 = !DILocation(line: 420, column: 6, scope: !761)
!761 = distinct !DILexicalBlock(scope: !70, file: !1, line: 420, column: 6)
!762 = !DILocation(line: 420, column: 20, scope: !761)
!763 = !DILocation(line: 420, column: 6, scope: !70)
!764 = !DILocation(line: 421, column: 3, scope: !765)
!765 = distinct !DILexicalBlock(scope: !761, file: !1, line: 420, column: 26)
!766 = !DILocation(line: 421, column: 11, scope: !767)
!767 = !DILexicalBlockFile(scope: !768, file: !1, discriminator: 1)
!768 = distinct !DILexicalBlock(scope: !769, file: !1, line: 421, column: 3)
!769 = distinct !DILexicalBlock(scope: !765, file: !1, line: 421, column: 3)
!770 = !DILocation(line: 421, column: 23, scope: !767)
!771 = !DILocation(line: 421, column: 20, scope: !767)
!772 = !DILocation(line: 421, column: 3, scope: !767)
!773 = !DILocation(line: 422, column: 10, scope: !774)
!774 = distinct !DILexicalBlock(scope: !768, file: !1, line: 422, column: 8)
!775 = !DILocation(line: 422, column: 16, scope: !774)
!776 = !DILocation(line: 422, column: 14, scope: !774)
!777 = !DILocation(line: 422, column: 27, scope: !774)
!778 = !DILocation(line: 422, column: 25, scope: !774)
!779 = !DILocation(line: 422, column: 8, scope: !774)
!780 = !DILocation(line: 422, column: 42, scope: !774)
!781 = !DILocation(line: 422, column: 38, scope: !774)
!782 = !DILocation(line: 422, column: 35, scope: !774)
!783 = !DILocation(line: 422, column: 8, scope: !768)
!784 = !DILocation(line: 423, column: 5, scope: !774)
!785 = !DILocation(line: 422, column: 50, scope: !786)
!786 = !DILexicalBlockFile(scope: !774, file: !1, discriminator: 1)
!787 = !DILocation(line: 421, column: 34, scope: !788)
!788 = !DILexicalBlockFile(scope: !768, file: !1, discriminator: 2)
!789 = !DILocation(line: 421, column: 3, scope: !788)
!790 = !DILocation(line: 425, column: 36, scope: !765)
!791 = !DILocation(line: 425, column: 11, scope: !765)
!792 = !DILocation(line: 425, column: 25, scope: !765)
!793 = !DILocation(line: 425, column: 3, scope: !765)
!794 = !DILocation(line: 425, column: 30, scope: !765)
!795 = !DILocation(line: 425, column: 34, scope: !765)
!796 = !DILocation(line: 427, column: 7, scope: !797)
!797 = distinct !DILexicalBlock(scope: !765, file: !1, line: 427, column: 7)
!798 = !DILocation(line: 427, column: 19, scope: !797)
!799 = !DILocation(line: 427, column: 16, scope: !797)
!800 = !DILocation(line: 427, column: 7, scope: !765)
!801 = !DILocation(line: 428, column: 4, scope: !802)
!802 = distinct !DILexicalBlock(scope: !797, file: !1, line: 427, column: 30)
!803 = !DILocation(line: 428, column: 4, scope: !804)
!804 = !DILexicalBlockFile(scope: !805, file: !1, discriminator: 1)
!805 = distinct !DILexicalBlock(scope: !802, file: !1, line: 428, column: 4)
!806 = !DILocation(line: 429, column: 11, scope: !802)
!807 = !DILocation(line: 429, column: 4, scope: !802)
!808 = !DILocation(line: 431, column: 2, scope: !765)
!809 = !DILocation(line: 433, column: 6, scope: !810)
!810 = distinct !DILexicalBlock(scope: !70, file: !1, line: 433, column: 6)
!811 = !DILocation(line: 433, column: 15, scope: !810)
!812 = !DILocation(line: 433, column: 6, scope: !70)
!813 = !DILocation(line: 434, column: 12, scope: !810)
!814 = !DILocation(line: 434, column: 3, scope: !810)
!815 = !DILocation(line: 436, column: 2, scope: !70)
!816 = !DILocation(line: 436, column: 2, scope: !817)
!817 = !DILexicalBlockFile(scope: !818, file: !1, discriminator: 1)
!818 = distinct !DILexicalBlock(scope: !70, file: !1, line: 436, column: 2)
!819 = !DILocation(line: 436, column: 2, scope: !820)
!820 = !DILexicalBlockFile(scope: !817, file: !1, discriminator: 2)
!821 = !DILocation(line: 437, column: 1, scope: !70)
!822 = !DILocalVariable(name: "mf", arg: 1, scope: !71, file: !1, line: 441, type: !22)
!823 = !DILocation(line: 441, column: 27, scope: !71)
!824 = !DILocalVariable(name: "amount", arg: 2, scope: !71, file: !1, line: 441, type: !11)
!825 = !DILocation(line: 441, column: 40, scope: !71)
!826 = !DILocation(line: 443, column: 2, scope: !71)
!827 = !DILocalVariable(name: "cur", scope: !828, file: !1, line: 444, type: !96)
!828 = distinct !DILexicalBlock(scope: !71, file: !1, line: 443, column: 5)
!829 = !DILocation(line: 444, column: 18, scope: !828)
!830 = !DILocalVariable(name: "pos", scope: !828, file: !1, line: 445, type: !11)
!831 = !DILocation(line: 445, column: 12, scope: !828)
!832 = !DILocalVariable(name: "temp", scope: !828, file: !1, line: 446, type: !11)
!833 = !DILocation(line: 446, column: 12, scope: !828)
!834 = !DILocalVariable(name: "hash_value", scope: !828, file: !1, line: 446, type: !11)
!835 = !DILocation(line: 446, column: 18, scope: !828)
!836 = !DILocalVariable(name: "hash_2_value", scope: !828, file: !1, line: 446, type: !11)
!837 = !DILocation(line: 446, column: 30, scope: !828)
!838 = !DILocalVariable(name: "hash_3_value", scope: !828, file: !1, line: 446, type: !11)
!839 = !DILocation(line: 446, column: 44, scope: !828)
!840 = !DILocalVariable(name: "cur_match", scope: !828, file: !1, line: 447, type: !11)
!841 = !DILocation(line: 447, column: 12, scope: !828)
!842 = !DILocation(line: 449, column: 16, scope: !843)
!843 = distinct !DILexicalBlock(scope: !828, file: !1, line: 449, column: 7)
!844 = !DILocation(line: 449, column: 7, scope: !843)
!845 = !DILocation(line: 449, column: 20, scope: !843)
!846 = !DILocation(line: 449, column: 7, scope: !828)
!847 = !DILocation(line: 450, column: 17, scope: !848)
!848 = distinct !DILexicalBlock(scope: !843, file: !1, line: 449, column: 25)
!849 = !DILocation(line: 450, column: 4, scope: !848)
!850 = !DILocation(line: 451, column: 4, scope: !848)
!851 = !DILocation(line: 454, column: 16, scope: !828)
!852 = !DILocation(line: 454, column: 9, scope: !828)
!853 = !DILocation(line: 454, column: 7, scope: !828)
!854 = !DILocation(line: 455, column: 9, scope: !828)
!855 = !DILocation(line: 455, column: 13, scope: !828)
!856 = !DILocation(line: 455, column: 24, scope: !828)
!857 = !DILocation(line: 455, column: 28, scope: !828)
!858 = !DILocation(line: 455, column: 22, scope: !828)
!859 = !DILocation(line: 455, column: 7, scope: !828)
!860 = !DILocation(line: 457, column: 3, scope: !828)
!861 = !DILocation(line: 459, column: 42, scope: !828)
!862 = !DILocation(line: 459, column: 40, scope: !828)
!863 = !DILocation(line: 459, column: 15, scope: !828)
!864 = !DILocation(line: 459, column: 19, scope: !828)
!865 = !DILocation(line: 459, column: 13, scope: !828)
!866 = !DILocation(line: 461, column: 28, scope: !828)
!867 = !DILocation(line: 461, column: 12, scope: !828)
!868 = !DILocation(line: 461, column: 3, scope: !828)
!869 = !DILocation(line: 461, column: 7, scope: !828)
!870 = !DILocation(line: 461, column: 26, scope: !828)
!871 = !DILocation(line: 462, column: 46, scope: !828)
!872 = !DILocation(line: 462, column: 30, scope: !828)
!873 = !DILocation(line: 462, column: 28, scope: !828)
!874 = !DILocation(line: 462, column: 3, scope: !828)
!875 = !DILocation(line: 462, column: 7, scope: !828)
!876 = !DILocation(line: 462, column: 44, scope: !828)
!877 = !DILocation(line: 463, column: 44, scope: !828)
!878 = !DILocation(line: 463, column: 30, scope: !828)
!879 = !DILocation(line: 463, column: 28, scope: !828)
!880 = !DILocation(line: 463, column: 3, scope: !828)
!881 = !DILocation(line: 463, column: 7, scope: !828)
!882 = !DILocation(line: 463, column: 42, scope: !828)
!883 = !DILocation(line: 465, column: 3, scope: !828)
!884 = !DILocation(line: 465, column: 3, scope: !885)
!885 = !DILexicalBlockFile(scope: !886, file: !1, discriminator: 1)
!886 = distinct !DILexicalBlock(scope: !828, file: !1, line: 465, column: 3)
!887 = !DILocation(line: 467, column: 2, scope: !828)
!888 = !DILocation(line: 467, column: 11, scope: !889)
!889 = !DILexicalBlockFile(scope: !71, file: !1, discriminator: 1)
!890 = !DILocation(line: 467, column: 20, scope: !889)
!891 = !DILocation(line: 467, column: 2, scope: !889)
!892 = !DILocation(line: 468, column: 1, scope: !71)
!893 = !DILocalVariable(name: "mf", arg: 1, scope: !72, file: !1, line: 627, type: !22)
!894 = !DILocation(line: 627, column: 27, scope: !72)
!895 = !DILocalVariable(name: "matches", arg: 2, scope: !72, file: !1, line: 627, type: !44)
!896 = !DILocation(line: 627, column: 43, scope: !72)
!897 = !DILocalVariable(name: "cur", scope: !72, file: !1, line: 629, type: !96)
!898 = !DILocation(line: 629, column: 17, scope: !72)
!899 = !DILocalVariable(name: "pos", scope: !72, file: !1, line: 630, type: !11)
!900 = !DILocation(line: 630, column: 11, scope: !72)
!901 = !DILocalVariable(name: "hash_value", scope: !72, file: !1, line: 631, type: !11)
!902 = !DILocation(line: 631, column: 11, scope: !72)
!903 = !DILocalVariable(name: "cur_match", scope: !72, file: !1, line: 632, type: !11)
!904 = !DILocation(line: 632, column: 11, scope: !72)
!905 = !DILocalVariable(name: "matches_count", scope: !72, file: !1, line: 633, type: !11)
!906 = !DILocation(line: 633, column: 11, scope: !72)
!907 = !DILocalVariable(name: "len_limit", scope: !72, file: !1, line: 635, type: !11)
!908 = !DILocation(line: 635, column: 2, scope: !72)
!909 = !DILocation(line: 635, column: 2, scope: !910)
!910 = distinct !DILexicalBlock(scope: !72, file: !1, line: 635, column: 2)
!911 = !DILocation(line: 635, column: 2, scope: !912)
!912 = !DILexicalBlockFile(scope: !913, file: !1, discriminator: 1)
!913 = distinct !DILexicalBlock(scope: !910, file: !1, line: 635, column: 2)
!914 = !DILocation(line: 635, column: 2, scope: !915)
!915 = !DILexicalBlockFile(scope: !916, file: !1, discriminator: 2)
!916 = distinct !DILexicalBlock(scope: !910, file: !1, line: 635, column: 2)
!917 = !DILocation(line: 635, column: 2, scope: !918)
!918 = !DILexicalBlockFile(scope: !916, file: !1, discriminator: 3)
!919 = !DILocation(line: 635, column: 2, scope: !920)
!920 = !DILexicalBlockFile(scope: !921, file: !1, discriminator: 4)
!921 = distinct !DILexicalBlock(scope: !916, file: !1, line: 635, column: 2)
!922 = !DILocation(line: 635, column: 2, scope: !923)
!923 = !DILexicalBlockFile(scope: !921, file: !1, discriminator: 5)
!924 = !DILocation(line: 635, column: 2, scope: !925)
!925 = !DILexicalBlockFile(scope: !921, file: !1, discriminator: 6)
!926 = !DILocation(line: 635, column: 2, scope: !927)
!927 = !DILexicalBlockFile(scope: !921, file: !1, discriminator: 7)
!928 = !DILocation(line: 635, column: 2, scope: !929)
!929 = !DILexicalBlockFile(scope: !921, file: !1, discriminator: 8)
!930 = !DILocation(line: 635, column: 2, scope: !931)
!931 = !DILexicalBlockFile(scope: !72, file: !1, discriminator: 9)
!932 = !DILocation(line: 637, column: 2, scope: !72)
!933 = !DILocation(line: 639, column: 23, scope: !72)
!934 = !DILocation(line: 639, column: 14, scope: !72)
!935 = !DILocation(line: 639, column: 18, scope: !72)
!936 = !DILocation(line: 639, column: 12, scope: !72)
!937 = !DILocation(line: 640, column: 25, scope: !72)
!938 = !DILocation(line: 640, column: 11, scope: !72)
!939 = !DILocation(line: 640, column: 2, scope: !72)
!940 = !DILocation(line: 640, column: 6, scope: !72)
!941 = !DILocation(line: 640, column: 23, scope: !72)
!942 = !DILocation(line: 642, column: 2, scope: !72)
!943 = !DILocation(line: 642, column: 2, scope: !944)
!944 = !DILexicalBlockFile(scope: !945, file: !1, discriminator: 1)
!945 = distinct !DILexicalBlock(scope: !72, file: !1, line: 642, column: 2)
!946 = !DILocation(line: 642, column: 2, scope: !947)
!947 = !DILexicalBlockFile(scope: !944, file: !1, discriminator: 2)
!948 = !DILocation(line: 643, column: 1, scope: !72)
!949 = !DILocalVariable(name: "len_limit", arg: 1, scope: !99, file: !1, line: 479, type: !94)
!950 = !DILocation(line: 479, column: 18, scope: !99)
!951 = !DILocalVariable(name: "pos", arg: 2, scope: !99, file: !1, line: 480, type: !94)
!952 = !DILocation(line: 480, column: 18, scope: !99)
!953 = !DILocalVariable(name: "cur", arg: 3, scope: !99, file: !1, line: 481, type: !95)
!954 = !DILocation(line: 481, column: 24, scope: !99)
!955 = !DILocalVariable(name: "cur_match", arg: 4, scope: !99, file: !1, line: 482, type: !11)
!956 = !DILocation(line: 482, column: 12, scope: !99)
!957 = !DILocalVariable(name: "depth", arg: 5, scope: !99, file: !1, line: 483, type: !11)
!958 = !DILocation(line: 483, column: 12, scope: !99)
!959 = !DILocalVariable(name: "son", arg: 6, scope: !99, file: !1, line: 484, type: !98)
!960 = !DILocation(line: 484, column: 19, scope: !99)
!961 = !DILocalVariable(name: "cyclic_pos", arg: 7, scope: !99, file: !1, line: 485, type: !94)
!962 = !DILocation(line: 485, column: 18, scope: !99)
!963 = !DILocalVariable(name: "cyclic_size", arg: 8, scope: !99, file: !1, line: 486, type: !94)
!964 = !DILocation(line: 486, column: 18, scope: !99)
!965 = !DILocalVariable(name: "matches", arg: 9, scope: !99, file: !1, line: 487, type: !44)
!966 = !DILocation(line: 487, column: 15, scope: !99)
!967 = !DILocalVariable(name: "len_best", arg: 10, scope: !99, file: !1, line: 488, type: !11)
!968 = !DILocation(line: 488, column: 12, scope: !99)
!969 = !DILocalVariable(name: "ptr0", scope: !99, file: !1, line: 490, type: !55)
!970 = !DILocation(line: 490, column: 12, scope: !99)
!971 = !DILocation(line: 490, column: 19, scope: !99)
!972 = !DILocation(line: 490, column: 26, scope: !99)
!973 = !DILocation(line: 490, column: 37, scope: !99)
!974 = !DILocation(line: 490, column: 23, scope: !99)
!975 = !DILocation(line: 490, column: 43, scope: !99)
!976 = !DILocalVariable(name: "ptr1", scope: !99, file: !1, line: 491, type: !55)
!977 = !DILocation(line: 491, column: 12, scope: !99)
!978 = !DILocation(line: 491, column: 19, scope: !99)
!979 = !DILocation(line: 491, column: 26, scope: !99)
!980 = !DILocation(line: 491, column: 37, scope: !99)
!981 = !DILocation(line: 491, column: 23, scope: !99)
!982 = !DILocalVariable(name: "len0", scope: !99, file: !1, line: 493, type: !11)
!983 = !DILocation(line: 493, column: 11, scope: !99)
!984 = !DILocalVariable(name: "len1", scope: !99, file: !1, line: 494, type: !11)
!985 = !DILocation(line: 494, column: 11, scope: !99)
!986 = !DILocation(line: 496, column: 2, scope: !99)
!987 = !DILocalVariable(name: "pair", scope: !988, file: !1, line: 497, type: !55)
!988 = distinct !DILexicalBlock(scope: !99, file: !1, line: 496, column: 15)
!989 = !DILocation(line: 497, column: 13, scope: !988)
!990 = !DILocalVariable(name: "pb", scope: !988, file: !1, line: 498, type: !96)
!991 = !DILocation(line: 498, column: 18, scope: !988)
!992 = !DILocalVariable(name: "len", scope: !988, file: !1, line: 499, type: !11)
!993 = !DILocation(line: 499, column: 12, scope: !988)
!994 = !DILocalVariable(name: "delta", scope: !988, file: !1, line: 501, type: !94)
!995 = !DILocation(line: 501, column: 18, scope: !988)
!996 = !DILocation(line: 501, column: 26, scope: !988)
!997 = !DILocation(line: 501, column: 32, scope: !988)
!998 = !DILocation(line: 501, column: 30, scope: !988)
!999 = !DILocation(line: 502, column: 12, scope: !1000)
!1000 = distinct !DILexicalBlock(scope: !988, file: !1, line: 502, column: 7)
!1001 = !DILocation(line: 502, column: 15, scope: !1000)
!1002 = !DILocation(line: 502, column: 20, scope: !1000)
!1003 = !DILocation(line: 502, column: 23, scope: !1004)
!1004 = !DILexicalBlockFile(scope: !1000, file: !1, discriminator: 1)
!1005 = !DILocation(line: 502, column: 32, scope: !1004)
!1006 = !DILocation(line: 502, column: 29, scope: !1004)
!1007 = !DILocation(line: 502, column: 7, scope: !1004)
!1008 = !DILocation(line: 503, column: 5, scope: !1009)
!1009 = distinct !DILexicalBlock(scope: !1000, file: !1, line: 502, column: 45)
!1010 = !DILocation(line: 503, column: 10, scope: !1009)
!1011 = !DILocation(line: 504, column: 5, scope: !1009)
!1012 = !DILocation(line: 504, column: 10, scope: !1009)
!1013 = !DILocation(line: 505, column: 11, scope: !1009)
!1014 = !DILocation(line: 505, column: 4, scope: !1009)
!1015 = !DILocation(line: 508, column: 10, scope: !988)
!1016 = !DILocation(line: 508, column: 18, scope: !988)
!1017 = !DILocation(line: 508, column: 31, scope: !988)
!1018 = !DILocation(line: 508, column: 29, scope: !988)
!1019 = !DILocation(line: 509, column: 8, scope: !988)
!1020 = !DILocation(line: 509, column: 16, scope: !988)
!1021 = !DILocation(line: 509, column: 14, scope: !988)
!1022 = !DILocation(line: 509, column: 29, scope: !1023)
!1023 = !DILexicalBlockFile(scope: !988, file: !1, discriminator: 1)
!1024 = !DILocation(line: 509, column: 8, scope: !1023)
!1025 = !DILocation(line: 509, column: 8, scope: !1026)
!1026 = !DILexicalBlockFile(scope: !988, file: !1, discriminator: 2)
!1027 = !DILocation(line: 509, column: 8, scope: !1028)
!1028 = !DILexicalBlockFile(scope: !988, file: !1, discriminator: 3)
!1029 = !DILocation(line: 509, column: 5, scope: !1028)
!1030 = !DILocation(line: 510, column: 5, scope: !988)
!1031 = !DILocation(line: 508, column: 14, scope: !1023)
!1032 = !DILocation(line: 508, column: 8, scope: !1023)
!1033 = !DILocation(line: 512, column: 8, scope: !988)
!1034 = !DILocation(line: 512, column: 14, scope: !988)
!1035 = !DILocation(line: 512, column: 12, scope: !988)
!1036 = !DILocation(line: 512, column: 6, scope: !988)
!1037 = !DILocation(line: 513, column: 9, scope: !988)
!1038 = !DILocation(line: 513, column: 9, scope: !1023)
!1039 = !DILocation(line: 513, column: 9, scope: !1026)
!1040 = !DILocation(line: 513, column: 9, scope: !1028)
!1041 = !DILocation(line: 513, column: 7, scope: !1028)
!1042 = !DILocation(line: 515, column: 10, scope: !1043)
!1043 = distinct !DILexicalBlock(scope: !988, file: !1, line: 515, column: 7)
!1044 = !DILocation(line: 515, column: 7, scope: !1043)
!1045 = !DILocation(line: 515, column: 22, scope: !1043)
!1046 = !DILocation(line: 515, column: 18, scope: !1043)
!1047 = !DILocation(line: 515, column: 15, scope: !1043)
!1048 = !DILocation(line: 515, column: 7, scope: !988)
!1049 = !DILocation(line: 516, column: 4, scope: !1050)
!1050 = distinct !DILexicalBlock(scope: !1043, file: !1, line: 515, column: 28)
!1051 = !DILocation(line: 516, column: 11, scope: !1052)
!1052 = !DILexicalBlockFile(scope: !1050, file: !1, discriminator: 1)
!1053 = !DILocation(line: 516, column: 20, scope: !1052)
!1054 = !DILocation(line: 516, column: 17, scope: !1052)
!1055 = !DILocation(line: 516, column: 4, scope: !1052)
!1056 = !DILocation(line: 517, column: 12, scope: !1057)
!1057 = distinct !DILexicalBlock(scope: !1050, file: !1, line: 517, column: 9)
!1058 = !DILocation(line: 517, column: 9, scope: !1057)
!1059 = !DILocation(line: 517, column: 24, scope: !1057)
!1060 = !DILocation(line: 517, column: 20, scope: !1057)
!1061 = !DILocation(line: 517, column: 17, scope: !1057)
!1062 = !DILocation(line: 517, column: 9, scope: !1050)
!1063 = !DILocation(line: 518, column: 6, scope: !1057)
!1064 = !DILocation(line: 516, column: 4, scope: !1065)
!1065 = !DILexicalBlockFile(scope: !1050, file: !1, discriminator: 2)
!1066 = !DILocation(line: 520, column: 8, scope: !1067)
!1067 = distinct !DILexicalBlock(scope: !1050, file: !1, line: 520, column: 8)
!1068 = !DILocation(line: 520, column: 19, scope: !1067)
!1069 = !DILocation(line: 520, column: 17, scope: !1067)
!1070 = !DILocation(line: 520, column: 8, scope: !1050)
!1071 = !DILocation(line: 521, column: 16, scope: !1072)
!1072 = distinct !DILexicalBlock(scope: !1067, file: !1, line: 520, column: 24)
!1073 = !DILocation(line: 521, column: 14, scope: !1072)
!1074 = !DILocation(line: 522, column: 20, scope: !1072)
!1075 = !DILocation(line: 522, column: 5, scope: !1072)
!1076 = !DILocation(line: 522, column: 14, scope: !1072)
!1077 = !DILocation(line: 522, column: 18, scope: !1072)
!1078 = !DILocation(line: 523, column: 21, scope: !1072)
!1079 = !DILocation(line: 523, column: 27, scope: !1072)
!1080 = !DILocation(line: 523, column: 5, scope: !1072)
!1081 = !DILocation(line: 523, column: 14, scope: !1072)
!1082 = !DILocation(line: 523, column: 19, scope: !1072)
!1083 = !DILocation(line: 524, column: 5, scope: !1072)
!1084 = !DILocation(line: 526, column: 9, scope: !1085)
!1085 = distinct !DILexicalBlock(scope: !1072, file: !1, line: 526, column: 9)
!1086 = !DILocation(line: 526, column: 16, scope: !1085)
!1087 = !DILocation(line: 526, column: 13, scope: !1085)
!1088 = !DILocation(line: 526, column: 9, scope: !1072)
!1089 = !DILocation(line: 527, column: 14, scope: !1090)
!1090 = distinct !DILexicalBlock(scope: !1085, file: !1, line: 526, column: 27)
!1091 = !DILocation(line: 527, column: 7, scope: !1090)
!1092 = !DILocation(line: 527, column: 12, scope: !1090)
!1093 = !DILocation(line: 528, column: 14, scope: !1090)
!1094 = !DILocation(line: 528, column: 7, scope: !1090)
!1095 = !DILocation(line: 528, column: 12, scope: !1090)
!1096 = !DILocation(line: 529, column: 13, scope: !1090)
!1097 = !DILocation(line: 529, column: 6, scope: !1090)
!1098 = !DILocation(line: 531, column: 4, scope: !1072)
!1099 = !DILocation(line: 532, column: 3, scope: !1050)
!1100 = !DILocation(line: 534, column: 10, scope: !1101)
!1101 = distinct !DILexicalBlock(scope: !988, file: !1, line: 534, column: 7)
!1102 = !DILocation(line: 534, column: 7, scope: !1101)
!1103 = !DILocation(line: 534, column: 21, scope: !1101)
!1104 = !DILocation(line: 534, column: 17, scope: !1101)
!1105 = !DILocation(line: 534, column: 15, scope: !1101)
!1106 = !DILocation(line: 534, column: 7, scope: !988)
!1107 = !DILocation(line: 535, column: 12, scope: !1108)
!1108 = distinct !DILexicalBlock(scope: !1101, file: !1, line: 534, column: 27)
!1109 = !DILocation(line: 535, column: 5, scope: !1108)
!1110 = !DILocation(line: 535, column: 10, scope: !1108)
!1111 = !DILocation(line: 536, column: 11, scope: !1108)
!1112 = !DILocation(line: 536, column: 16, scope: !1108)
!1113 = !DILocation(line: 536, column: 9, scope: !1108)
!1114 = !DILocation(line: 537, column: 17, scope: !1108)
!1115 = !DILocation(line: 537, column: 16, scope: !1108)
!1116 = !DILocation(line: 537, column: 14, scope: !1108)
!1117 = !DILocation(line: 538, column: 11, scope: !1108)
!1118 = !DILocation(line: 538, column: 9, scope: !1108)
!1119 = !DILocation(line: 539, column: 3, scope: !1108)
!1120 = !DILocation(line: 540, column: 12, scope: !1121)
!1121 = distinct !DILexicalBlock(scope: !1101, file: !1, line: 539, column: 10)
!1122 = !DILocation(line: 540, column: 5, scope: !1121)
!1123 = !DILocation(line: 540, column: 10, scope: !1121)
!1124 = !DILocation(line: 541, column: 11, scope: !1121)
!1125 = !DILocation(line: 541, column: 9, scope: !1121)
!1126 = !DILocation(line: 542, column: 17, scope: !1121)
!1127 = !DILocation(line: 542, column: 16, scope: !1121)
!1128 = !DILocation(line: 542, column: 14, scope: !1121)
!1129 = !DILocation(line: 543, column: 11, scope: !1121)
!1130 = !DILocation(line: 543, column: 9, scope: !1121)
!1131 = !DILocation(line: 496, column: 2, scope: !1132)
!1132 = !DILexicalBlockFile(scope: !99, file: !1, discriminator: 1)
!1133 = !DILocation(line: 546, column: 1, scope: !99)
!1134 = !DILocalVariable(name: "mf", arg: 1, scope: !73, file: !1, line: 647, type: !22)
!1135 = !DILocation(line: 647, column: 27, scope: !73)
!1136 = !DILocalVariable(name: "amount", arg: 2, scope: !73, file: !1, line: 647, type: !11)
!1137 = !DILocation(line: 647, column: 40, scope: !73)
!1138 = !DILocation(line: 649, column: 2, scope: !73)
!1139 = !DILocalVariable(name: "cur", scope: !1140, file: !1, line: 650, type: !96)
!1140 = distinct !DILexicalBlock(scope: !73, file: !1, line: 649, column: 5)
!1141 = !DILocation(line: 650, column: 18, scope: !1140)
!1142 = !DILocalVariable(name: "pos", scope: !1140, file: !1, line: 651, type: !11)
!1143 = !DILocation(line: 651, column: 12, scope: !1140)
!1144 = !DILocalVariable(name: "hash_value", scope: !1140, file: !1, line: 652, type: !11)
!1145 = !DILocation(line: 652, column: 12, scope: !1140)
!1146 = !DILocalVariable(name: "cur_match", scope: !1140, file: !1, line: 653, type: !11)
!1147 = !DILocation(line: 653, column: 12, scope: !1140)
!1148 = !DILocalVariable(name: "len_limit", scope: !1140, file: !1, line: 655, type: !11)
!1149 = !DILocation(line: 655, column: 3, scope: !1140)
!1150 = !DILocation(line: 655, column: 3, scope: !1151)
!1151 = distinct !DILexicalBlock(scope: !1140, file: !1, line: 655, column: 3)
!1152 = !DILocation(line: 655, column: 3, scope: !1153)
!1153 = !DILexicalBlockFile(scope: !1154, file: !1, discriminator: 1)
!1154 = distinct !DILexicalBlock(scope: !1151, file: !1, line: 655, column: 3)
!1155 = !DILocation(line: 655, column: 3, scope: !1156)
!1156 = !DILexicalBlockFile(scope: !1157, file: !1, discriminator: 2)
!1157 = distinct !DILexicalBlock(scope: !1151, file: !1, line: 655, column: 3)
!1158 = !DILocation(line: 655, column: 3, scope: !1159)
!1159 = !DILexicalBlockFile(scope: !1157, file: !1, discriminator: 3)
!1160 = !DILocation(line: 655, column: 3, scope: !1161)
!1161 = !DILexicalBlockFile(scope: !1162, file: !1, discriminator: 4)
!1162 = distinct !DILexicalBlock(scope: !1157, file: !1, line: 655, column: 3)
!1163 = !DILocation(line: 655, column: 3, scope: !1164)
!1164 = !DILexicalBlockFile(scope: !1162, file: !1, discriminator: 5)
!1165 = !DILocation(line: 655, column: 3, scope: !1166)
!1166 = !DILexicalBlockFile(scope: !1162, file: !1, discriminator: 6)
!1167 = !DILocation(line: 655, column: 3, scope: !1168)
!1168 = !DILexicalBlockFile(scope: !1162, file: !1, discriminator: 7)
!1169 = !DILocation(line: 655, column: 3, scope: !1170)
!1170 = !DILexicalBlockFile(scope: !1162, file: !1, discriminator: 8)
!1171 = !DILocation(line: 655, column: 3, scope: !1172)
!1172 = !DILexicalBlockFile(scope: !1140, file: !1, discriminator: 9)
!1173 = !DILocation(line: 657, column: 3, scope: !1140)
!1174 = !DILocation(line: 659, column: 24, scope: !1140)
!1175 = !DILocation(line: 659, column: 15, scope: !1140)
!1176 = !DILocation(line: 659, column: 19, scope: !1140)
!1177 = !DILocation(line: 659, column: 13, scope: !1140)
!1178 = !DILocation(line: 660, column: 26, scope: !1140)
!1179 = !DILocation(line: 660, column: 12, scope: !1140)
!1180 = !DILocation(line: 660, column: 3, scope: !1140)
!1181 = !DILocation(line: 660, column: 7, scope: !1140)
!1182 = !DILocation(line: 660, column: 24, scope: !1140)
!1183 = !DILocation(line: 662, column: 3, scope: !1140)
!1184 = !DILocation(line: 662, column: 3, scope: !1185)
!1185 = !DILexicalBlockFile(scope: !1186, file: !1, discriminator: 1)
!1186 = distinct !DILexicalBlock(scope: !1140, file: !1, line: 662, column: 3)
!1187 = !DILocation(line: 662, column: 3, scope: !1188)
!1188 = !DILexicalBlockFile(scope: !1185, file: !1, discriminator: 2)
!1189 = !DILocation(line: 664, column: 2, scope: !1140)
!1190 = !DILocation(line: 664, column: 11, scope: !1191)
!1191 = !DILexicalBlockFile(scope: !73, file: !1, discriminator: 1)
!1192 = !DILocation(line: 664, column: 20, scope: !1191)
!1193 = !DILocation(line: 664, column: 2, scope: !1191)
!1194 = !DILocation(line: 665, column: 1, scope: !73)
!1195 = !DILocalVariable(name: "len_limit", arg: 1, scope: !100, file: !1, line: 551, type: !94)
!1196 = !DILocation(line: 551, column: 18, scope: !100)
!1197 = !DILocalVariable(name: "pos", arg: 2, scope: !100, file: !1, line: 552, type: !94)
!1198 = !DILocation(line: 552, column: 18, scope: !100)
!1199 = !DILocalVariable(name: "cur", arg: 3, scope: !100, file: !1, line: 553, type: !95)
!1200 = !DILocation(line: 553, column: 24, scope: !100)
!1201 = !DILocalVariable(name: "cur_match", arg: 4, scope: !100, file: !1, line: 554, type: !11)
!1202 = !DILocation(line: 554, column: 12, scope: !100)
!1203 = !DILocalVariable(name: "depth", arg: 5, scope: !100, file: !1, line: 555, type: !11)
!1204 = !DILocation(line: 555, column: 12, scope: !100)
!1205 = !DILocalVariable(name: "son", arg: 6, scope: !100, file: !1, line: 556, type: !98)
!1206 = !DILocation(line: 556, column: 19, scope: !100)
!1207 = !DILocalVariable(name: "cyclic_pos", arg: 7, scope: !100, file: !1, line: 557, type: !94)
!1208 = !DILocation(line: 557, column: 18, scope: !100)
!1209 = !DILocalVariable(name: "cyclic_size", arg: 8, scope: !100, file: !1, line: 558, type: !94)
!1210 = !DILocation(line: 558, column: 18, scope: !100)
!1211 = !DILocalVariable(name: "ptr0", scope: !100, file: !1, line: 560, type: !55)
!1212 = !DILocation(line: 560, column: 12, scope: !100)
!1213 = !DILocation(line: 560, column: 19, scope: !100)
!1214 = !DILocation(line: 560, column: 26, scope: !100)
!1215 = !DILocation(line: 560, column: 37, scope: !100)
!1216 = !DILocation(line: 560, column: 23, scope: !100)
!1217 = !DILocation(line: 560, column: 43, scope: !100)
!1218 = !DILocalVariable(name: "ptr1", scope: !100, file: !1, line: 561, type: !55)
!1219 = !DILocation(line: 561, column: 12, scope: !100)
!1220 = !DILocation(line: 561, column: 19, scope: !100)
!1221 = !DILocation(line: 561, column: 26, scope: !100)
!1222 = !DILocation(line: 561, column: 37, scope: !100)
!1223 = !DILocation(line: 561, column: 23, scope: !100)
!1224 = !DILocalVariable(name: "len0", scope: !100, file: !1, line: 563, type: !11)
!1225 = !DILocation(line: 563, column: 11, scope: !100)
!1226 = !DILocalVariable(name: "len1", scope: !100, file: !1, line: 564, type: !11)
!1227 = !DILocation(line: 564, column: 11, scope: !100)
!1228 = !DILocation(line: 566, column: 2, scope: !100)
!1229 = !DILocalVariable(name: "pair", scope: !1230, file: !1, line: 567, type: !55)
!1230 = distinct !DILexicalBlock(scope: !100, file: !1, line: 566, column: 15)
!1231 = !DILocation(line: 567, column: 13, scope: !1230)
!1232 = !DILocalVariable(name: "pb", scope: !1230, file: !1, line: 568, type: !96)
!1233 = !DILocation(line: 568, column: 18, scope: !1230)
!1234 = !DILocalVariable(name: "len", scope: !1230, file: !1, line: 569, type: !11)
!1235 = !DILocation(line: 569, column: 12, scope: !1230)
!1236 = !DILocalVariable(name: "delta", scope: !1230, file: !1, line: 571, type: !94)
!1237 = !DILocation(line: 571, column: 18, scope: !1230)
!1238 = !DILocation(line: 571, column: 26, scope: !1230)
!1239 = !DILocation(line: 571, column: 32, scope: !1230)
!1240 = !DILocation(line: 571, column: 30, scope: !1230)
!1241 = !DILocation(line: 572, column: 12, scope: !1242)
!1242 = distinct !DILexicalBlock(scope: !1230, file: !1, line: 572, column: 7)
!1243 = !DILocation(line: 572, column: 15, scope: !1242)
!1244 = !DILocation(line: 572, column: 20, scope: !1242)
!1245 = !DILocation(line: 572, column: 23, scope: !1246)
!1246 = !DILexicalBlockFile(scope: !1242, file: !1, discriminator: 1)
!1247 = !DILocation(line: 572, column: 32, scope: !1246)
!1248 = !DILocation(line: 572, column: 29, scope: !1246)
!1249 = !DILocation(line: 572, column: 7, scope: !1246)
!1250 = !DILocation(line: 573, column: 5, scope: !1251)
!1251 = distinct !DILexicalBlock(scope: !1242, file: !1, line: 572, column: 45)
!1252 = !DILocation(line: 573, column: 10, scope: !1251)
!1253 = !DILocation(line: 574, column: 5, scope: !1251)
!1254 = !DILocation(line: 574, column: 10, scope: !1251)
!1255 = !DILocation(line: 575, column: 4, scope: !1251)
!1256 = !DILocation(line: 578, column: 10, scope: !1230)
!1257 = !DILocation(line: 578, column: 18, scope: !1230)
!1258 = !DILocation(line: 578, column: 31, scope: !1230)
!1259 = !DILocation(line: 578, column: 29, scope: !1230)
!1260 = !DILocation(line: 579, column: 8, scope: !1230)
!1261 = !DILocation(line: 579, column: 16, scope: !1230)
!1262 = !DILocation(line: 579, column: 14, scope: !1230)
!1263 = !DILocation(line: 579, column: 29, scope: !1264)
!1264 = !DILexicalBlockFile(scope: !1230, file: !1, discriminator: 1)
!1265 = !DILocation(line: 579, column: 8, scope: !1264)
!1266 = !DILocation(line: 579, column: 8, scope: !1267)
!1267 = !DILexicalBlockFile(scope: !1230, file: !1, discriminator: 2)
!1268 = !DILocation(line: 579, column: 8, scope: !1269)
!1269 = !DILexicalBlockFile(scope: !1230, file: !1, discriminator: 3)
!1270 = !DILocation(line: 579, column: 5, scope: !1269)
!1271 = !DILocation(line: 580, column: 5, scope: !1230)
!1272 = !DILocation(line: 578, column: 14, scope: !1264)
!1273 = !DILocation(line: 578, column: 8, scope: !1264)
!1274 = !DILocation(line: 581, column: 8, scope: !1230)
!1275 = !DILocation(line: 581, column: 14, scope: !1230)
!1276 = !DILocation(line: 581, column: 12, scope: !1230)
!1277 = !DILocation(line: 581, column: 6, scope: !1230)
!1278 = !DILocation(line: 582, column: 9, scope: !1230)
!1279 = !DILocation(line: 582, column: 9, scope: !1264)
!1280 = !DILocation(line: 582, column: 9, scope: !1267)
!1281 = !DILocation(line: 582, column: 9, scope: !1269)
!1282 = !DILocation(line: 582, column: 7, scope: !1269)
!1283 = !DILocation(line: 584, column: 10, scope: !1284)
!1284 = distinct !DILexicalBlock(scope: !1230, file: !1, line: 584, column: 7)
!1285 = !DILocation(line: 584, column: 7, scope: !1284)
!1286 = !DILocation(line: 584, column: 22, scope: !1284)
!1287 = !DILocation(line: 584, column: 18, scope: !1284)
!1288 = !DILocation(line: 584, column: 15, scope: !1284)
!1289 = !DILocation(line: 584, column: 7, scope: !1230)
!1290 = !DILocation(line: 585, column: 4, scope: !1291)
!1291 = distinct !DILexicalBlock(scope: !1284, file: !1, line: 584, column: 28)
!1292 = !DILocation(line: 585, column: 11, scope: !1293)
!1293 = !DILexicalBlockFile(scope: !1291, file: !1, discriminator: 1)
!1294 = !DILocation(line: 585, column: 20, scope: !1293)
!1295 = !DILocation(line: 585, column: 17, scope: !1293)
!1296 = !DILocation(line: 585, column: 4, scope: !1293)
!1297 = !DILocation(line: 586, column: 12, scope: !1298)
!1298 = distinct !DILexicalBlock(scope: !1291, file: !1, line: 586, column: 9)
!1299 = !DILocation(line: 586, column: 9, scope: !1298)
!1300 = !DILocation(line: 586, column: 24, scope: !1298)
!1301 = !DILocation(line: 586, column: 20, scope: !1298)
!1302 = !DILocation(line: 586, column: 17, scope: !1298)
!1303 = !DILocation(line: 586, column: 9, scope: !1291)
!1304 = !DILocation(line: 587, column: 6, scope: !1298)
!1305 = !DILocation(line: 585, column: 4, scope: !1306)
!1306 = !DILexicalBlockFile(scope: !1291, file: !1, discriminator: 2)
!1307 = !DILocation(line: 589, column: 8, scope: !1308)
!1308 = distinct !DILexicalBlock(scope: !1291, file: !1, line: 589, column: 8)
!1309 = !DILocation(line: 589, column: 15, scope: !1308)
!1310 = !DILocation(line: 589, column: 12, scope: !1308)
!1311 = !DILocation(line: 589, column: 8, scope: !1291)
!1312 = !DILocation(line: 590, column: 13, scope: !1313)
!1313 = distinct !DILexicalBlock(scope: !1308, file: !1, line: 589, column: 26)
!1314 = !DILocation(line: 590, column: 6, scope: !1313)
!1315 = !DILocation(line: 590, column: 11, scope: !1313)
!1316 = !DILocation(line: 591, column: 13, scope: !1313)
!1317 = !DILocation(line: 591, column: 6, scope: !1313)
!1318 = !DILocation(line: 591, column: 11, scope: !1313)
!1319 = !DILocation(line: 592, column: 5, scope: !1313)
!1320 = !DILocation(line: 594, column: 3, scope: !1291)
!1321 = !DILocation(line: 596, column: 10, scope: !1322)
!1322 = distinct !DILexicalBlock(scope: !1230, file: !1, line: 596, column: 7)
!1323 = !DILocation(line: 596, column: 7, scope: !1322)
!1324 = !DILocation(line: 596, column: 21, scope: !1322)
!1325 = !DILocation(line: 596, column: 17, scope: !1322)
!1326 = !DILocation(line: 596, column: 15, scope: !1322)
!1327 = !DILocation(line: 596, column: 7, scope: !1230)
!1328 = !DILocation(line: 597, column: 12, scope: !1329)
!1329 = distinct !DILexicalBlock(scope: !1322, file: !1, line: 596, column: 27)
!1330 = !DILocation(line: 597, column: 5, scope: !1329)
!1331 = !DILocation(line: 597, column: 10, scope: !1329)
!1332 = !DILocation(line: 598, column: 11, scope: !1329)
!1333 = !DILocation(line: 598, column: 16, scope: !1329)
!1334 = !DILocation(line: 598, column: 9, scope: !1329)
!1335 = !DILocation(line: 599, column: 17, scope: !1329)
!1336 = !DILocation(line: 599, column: 16, scope: !1329)
!1337 = !DILocation(line: 599, column: 14, scope: !1329)
!1338 = !DILocation(line: 600, column: 11, scope: !1329)
!1339 = !DILocation(line: 600, column: 9, scope: !1329)
!1340 = !DILocation(line: 601, column: 3, scope: !1329)
!1341 = !DILocation(line: 602, column: 12, scope: !1342)
!1342 = distinct !DILexicalBlock(scope: !1322, file: !1, line: 601, column: 10)
!1343 = !DILocation(line: 602, column: 5, scope: !1342)
!1344 = !DILocation(line: 602, column: 10, scope: !1342)
!1345 = !DILocation(line: 603, column: 11, scope: !1342)
!1346 = !DILocation(line: 603, column: 9, scope: !1342)
!1347 = !DILocation(line: 604, column: 17, scope: !1342)
!1348 = !DILocation(line: 604, column: 16, scope: !1342)
!1349 = !DILocation(line: 604, column: 14, scope: !1342)
!1350 = !DILocation(line: 605, column: 11, scope: !1342)
!1351 = !DILocation(line: 605, column: 9, scope: !1342)
!1352 = !DILocation(line: 566, column: 2, scope: !1353)
!1353 = !DILexicalBlockFile(scope: !100, file: !1, discriminator: 1)
!1354 = !DILocation(line: 608, column: 1, scope: !100)
!1355 = !DILocalVariable(name: "mf", arg: 1, scope: !74, file: !1, line: 671, type: !22)
!1356 = !DILocation(line: 671, column: 27, scope: !74)
!1357 = !DILocalVariable(name: "matches", arg: 2, scope: !74, file: !1, line: 671, type: !44)
!1358 = !DILocation(line: 671, column: 43, scope: !74)
!1359 = !DILocalVariable(name: "cur", scope: !74, file: !1, line: 673, type: !96)
!1360 = !DILocation(line: 673, column: 17, scope: !74)
!1361 = !DILocalVariable(name: "pos", scope: !74, file: !1, line: 674, type: !11)
!1362 = !DILocation(line: 674, column: 11, scope: !74)
!1363 = !DILocalVariable(name: "temp", scope: !74, file: !1, line: 675, type: !11)
!1364 = !DILocation(line: 675, column: 11, scope: !74)
!1365 = !DILocalVariable(name: "hash_value", scope: !74, file: !1, line: 675, type: !11)
!1366 = !DILocation(line: 675, column: 17, scope: !74)
!1367 = !DILocalVariable(name: "hash_2_value", scope: !74, file: !1, line: 675, type: !11)
!1368 = !DILocation(line: 675, column: 29, scope: !74)
!1369 = !DILocalVariable(name: "delta2", scope: !74, file: !1, line: 676, type: !11)
!1370 = !DILocation(line: 676, column: 11, scope: !74)
!1371 = !DILocalVariable(name: "cur_match", scope: !74, file: !1, line: 676, type: !11)
!1372 = !DILocation(line: 676, column: 19, scope: !74)
!1373 = !DILocalVariable(name: "len_best", scope: !74, file: !1, line: 677, type: !11)
!1374 = !DILocation(line: 677, column: 11, scope: !74)
!1375 = !DILocalVariable(name: "matches_count", scope: !74, file: !1, line: 678, type: !11)
!1376 = !DILocation(line: 678, column: 11, scope: !74)
!1377 = !DILocalVariable(name: "len_limit", scope: !74, file: !1, line: 680, type: !11)
!1378 = !DILocation(line: 680, column: 2, scope: !74)
!1379 = !DILocation(line: 680, column: 2, scope: !1380)
!1380 = distinct !DILexicalBlock(scope: !74, file: !1, line: 680, column: 2)
!1381 = !DILocation(line: 680, column: 2, scope: !1382)
!1382 = !DILexicalBlockFile(scope: !1383, file: !1, discriminator: 1)
!1383 = distinct !DILexicalBlock(scope: !1380, file: !1, line: 680, column: 2)
!1384 = !DILocation(line: 680, column: 2, scope: !1385)
!1385 = !DILexicalBlockFile(scope: !1386, file: !1, discriminator: 2)
!1386 = distinct !DILexicalBlock(scope: !1380, file: !1, line: 680, column: 2)
!1387 = !DILocation(line: 680, column: 2, scope: !1388)
!1388 = !DILexicalBlockFile(scope: !1386, file: !1, discriminator: 3)
!1389 = !DILocation(line: 680, column: 2, scope: !1390)
!1390 = !DILexicalBlockFile(scope: !1391, file: !1, discriminator: 4)
!1391 = distinct !DILexicalBlock(scope: !1386, file: !1, line: 680, column: 2)
!1392 = !DILocation(line: 680, column: 2, scope: !1393)
!1393 = !DILexicalBlockFile(scope: !1391, file: !1, discriminator: 5)
!1394 = !DILocation(line: 680, column: 2, scope: !1395)
!1395 = !DILexicalBlockFile(scope: !1391, file: !1, discriminator: 6)
!1396 = !DILocation(line: 680, column: 2, scope: !1397)
!1397 = !DILexicalBlockFile(scope: !1391, file: !1, discriminator: 7)
!1398 = !DILocation(line: 680, column: 2, scope: !1399)
!1399 = !DILexicalBlockFile(scope: !1391, file: !1, discriminator: 8)
!1400 = !DILocation(line: 680, column: 2, scope: !1401)
!1401 = !DILexicalBlockFile(scope: !74, file: !1, discriminator: 9)
!1402 = !DILocation(line: 682, column: 2, scope: !74)
!1403 = !DILocation(line: 684, column: 11, scope: !74)
!1404 = !DILocation(line: 684, column: 26, scope: !74)
!1405 = !DILocation(line: 684, column: 17, scope: !74)
!1406 = !DILocation(line: 684, column: 21, scope: !74)
!1407 = !DILocation(line: 684, column: 15, scope: !74)
!1408 = !DILocation(line: 684, column: 9, scope: !74)
!1409 = !DILocation(line: 685, column: 41, scope: !74)
!1410 = !DILocation(line: 685, column: 39, scope: !74)
!1411 = !DILocation(line: 685, column: 14, scope: !74)
!1412 = !DILocation(line: 685, column: 18, scope: !74)
!1413 = !DILocation(line: 685, column: 12, scope: !74)
!1414 = !DILocation(line: 687, column: 27, scope: !74)
!1415 = !DILocation(line: 687, column: 11, scope: !74)
!1416 = !DILocation(line: 687, column: 2, scope: !74)
!1417 = !DILocation(line: 687, column: 6, scope: !74)
!1418 = !DILocation(line: 687, column: 25, scope: !74)
!1419 = !DILocation(line: 688, column: 43, scope: !74)
!1420 = !DILocation(line: 688, column: 29, scope: !74)
!1421 = !DILocation(line: 688, column: 27, scope: !74)
!1422 = !DILocation(line: 688, column: 2, scope: !74)
!1423 = !DILocation(line: 688, column: 6, scope: !74)
!1424 = !DILocation(line: 688, column: 41, scope: !74)
!1425 = !DILocation(line: 690, column: 6, scope: !1426)
!1426 = distinct !DILexicalBlock(scope: !74, file: !1, line: 690, column: 6)
!1427 = !DILocation(line: 690, column: 15, scope: !1426)
!1428 = !DILocation(line: 690, column: 19, scope: !1426)
!1429 = !DILocation(line: 690, column: 13, scope: !1426)
!1430 = !DILocation(line: 690, column: 31, scope: !1426)
!1431 = !DILocation(line: 690, column: 36, scope: !1432)
!1432 = !DILexicalBlockFile(scope: !1426, file: !1, discriminator: 1)
!1433 = !DILocation(line: 690, column: 42, scope: !1432)
!1434 = !DILocation(line: 690, column: 40, scope: !1432)
!1435 = !DILocation(line: 690, column: 34, scope: !1432)
!1436 = !DILocation(line: 690, column: 54, scope: !1432)
!1437 = !DILocation(line: 690, column: 53, scope: !1432)
!1438 = !DILocation(line: 690, column: 50, scope: !1432)
!1439 = !DILocation(line: 690, column: 6, scope: !1432)
!1440 = !DILocation(line: 691, column: 3, scope: !1441)
!1441 = distinct !DILexicalBlock(scope: !1426, file: !1, line: 690, column: 59)
!1442 = !DILocation(line: 691, column: 11, scope: !1443)
!1443 = !DILexicalBlockFile(scope: !1444, file: !1, discriminator: 1)
!1444 = distinct !DILexicalBlock(scope: !1445, file: !1, line: 691, column: 3)
!1445 = distinct !DILexicalBlock(scope: !1441, file: !1, line: 691, column: 3)
!1446 = !DILocation(line: 691, column: 23, scope: !1443)
!1447 = !DILocation(line: 691, column: 20, scope: !1443)
!1448 = !DILocation(line: 691, column: 3, scope: !1443)
!1449 = !DILocation(line: 692, column: 10, scope: !1450)
!1450 = distinct !DILexicalBlock(scope: !1444, file: !1, line: 692, column: 8)
!1451 = !DILocation(line: 692, column: 16, scope: !1450)
!1452 = !DILocation(line: 692, column: 14, scope: !1450)
!1453 = !DILocation(line: 692, column: 27, scope: !1450)
!1454 = !DILocation(line: 692, column: 25, scope: !1450)
!1455 = !DILocation(line: 692, column: 8, scope: !1450)
!1456 = !DILocation(line: 692, column: 42, scope: !1450)
!1457 = !DILocation(line: 692, column: 38, scope: !1450)
!1458 = !DILocation(line: 692, column: 35, scope: !1450)
!1459 = !DILocation(line: 692, column: 8, scope: !1444)
!1460 = !DILocation(line: 693, column: 5, scope: !1450)
!1461 = !DILocation(line: 692, column: 50, scope: !1462)
!1462 = !DILexicalBlockFile(scope: !1450, file: !1, discriminator: 1)
!1463 = !DILocation(line: 691, column: 34, scope: !1464)
!1464 = !DILexicalBlockFile(scope: !1444, file: !1, discriminator: 2)
!1465 = !DILocation(line: 691, column: 3, scope: !1464)
!1466 = !DILocation(line: 695, column: 20, scope: !1441)
!1467 = !DILocation(line: 695, column: 3, scope: !1441)
!1468 = !DILocation(line: 695, column: 14, scope: !1441)
!1469 = !DILocation(line: 695, column: 18, scope: !1441)
!1470 = !DILocation(line: 696, column: 21, scope: !1441)
!1471 = !DILocation(line: 696, column: 28, scope: !1441)
!1472 = !DILocation(line: 696, column: 3, scope: !1441)
!1473 = !DILocation(line: 696, column: 14, scope: !1441)
!1474 = !DILocation(line: 696, column: 19, scope: !1441)
!1475 = !DILocation(line: 697, column: 17, scope: !1441)
!1476 = !DILocation(line: 699, column: 7, scope: !1477)
!1477 = distinct !DILexicalBlock(scope: !1441, file: !1, line: 699, column: 7)
!1478 = !DILocation(line: 699, column: 19, scope: !1477)
!1479 = !DILocation(line: 699, column: 16, scope: !1477)
!1480 = !DILocation(line: 699, column: 7, scope: !1441)
!1481 = !DILocation(line: 700, column: 4, scope: !1482)
!1482 = distinct !DILexicalBlock(scope: !1477, file: !1, line: 699, column: 30)
!1483 = !DILocation(line: 700, column: 4, scope: !1484)
!1484 = !DILexicalBlockFile(scope: !1485, file: !1, discriminator: 1)
!1485 = distinct !DILexicalBlock(scope: !1482, file: !1, line: 700, column: 4)
!1486 = !DILocation(line: 700, column: 4, scope: !1487)
!1487 = !DILexicalBlockFile(scope: !1484, file: !1, discriminator: 2)
!1488 = !DILocation(line: 701, column: 4, scope: !1482)
!1489 = !DILocation(line: 703, column: 2, scope: !1441)
!1490 = !DILocation(line: 705, column: 2, scope: !74)
!1491 = !DILocation(line: 705, column: 2, scope: !1492)
!1492 = !DILexicalBlockFile(scope: !1493, file: !1, discriminator: 1)
!1493 = distinct !DILexicalBlock(scope: !74, file: !1, line: 705, column: 2)
!1494 = !DILocation(line: 705, column: 2, scope: !1495)
!1495 = !DILexicalBlockFile(scope: !1492, file: !1, discriminator: 2)
!1496 = !DILocation(line: 706, column: 1, scope: !74)
!1497 = !DILocalVariable(name: "mf", arg: 1, scope: !75, file: !1, line: 710, type: !22)
!1498 = !DILocation(line: 710, column: 27, scope: !75)
!1499 = !DILocalVariable(name: "amount", arg: 2, scope: !75, file: !1, line: 710, type: !11)
!1500 = !DILocation(line: 710, column: 40, scope: !75)
!1501 = !DILocation(line: 712, column: 2, scope: !75)
!1502 = !DILocalVariable(name: "cur", scope: !1503, file: !1, line: 713, type: !96)
!1503 = distinct !DILexicalBlock(scope: !75, file: !1, line: 712, column: 5)
!1504 = !DILocation(line: 713, column: 18, scope: !1503)
!1505 = !DILocalVariable(name: "pos", scope: !1503, file: !1, line: 714, type: !11)
!1506 = !DILocation(line: 714, column: 12, scope: !1503)
!1507 = !DILocalVariable(name: "temp", scope: !1503, file: !1, line: 715, type: !11)
!1508 = !DILocation(line: 715, column: 12, scope: !1503)
!1509 = !DILocalVariable(name: "hash_value", scope: !1503, file: !1, line: 715, type: !11)
!1510 = !DILocation(line: 715, column: 18, scope: !1503)
!1511 = !DILocalVariable(name: "hash_2_value", scope: !1503, file: !1, line: 715, type: !11)
!1512 = !DILocation(line: 715, column: 30, scope: !1503)
!1513 = !DILocalVariable(name: "cur_match", scope: !1503, file: !1, line: 716, type: !11)
!1514 = !DILocation(line: 716, column: 12, scope: !1503)
!1515 = !DILocalVariable(name: "len_limit", scope: !1503, file: !1, line: 718, type: !11)
!1516 = !DILocation(line: 718, column: 3, scope: !1503)
!1517 = !DILocation(line: 718, column: 3, scope: !1518)
!1518 = distinct !DILexicalBlock(scope: !1503, file: !1, line: 718, column: 3)
!1519 = !DILocation(line: 718, column: 3, scope: !1520)
!1520 = !DILexicalBlockFile(scope: !1521, file: !1, discriminator: 1)
!1521 = distinct !DILexicalBlock(scope: !1518, file: !1, line: 718, column: 3)
!1522 = !DILocation(line: 718, column: 3, scope: !1523)
!1523 = !DILexicalBlockFile(scope: !1524, file: !1, discriminator: 2)
!1524 = distinct !DILexicalBlock(scope: !1518, file: !1, line: 718, column: 3)
!1525 = !DILocation(line: 718, column: 3, scope: !1526)
!1526 = !DILexicalBlockFile(scope: !1524, file: !1, discriminator: 3)
!1527 = !DILocation(line: 718, column: 3, scope: !1528)
!1528 = !DILexicalBlockFile(scope: !1529, file: !1, discriminator: 4)
!1529 = distinct !DILexicalBlock(scope: !1524, file: !1, line: 718, column: 3)
!1530 = !DILocation(line: 718, column: 3, scope: !1531)
!1531 = !DILexicalBlockFile(scope: !1529, file: !1, discriminator: 5)
!1532 = !DILocation(line: 718, column: 3, scope: !1533)
!1533 = !DILexicalBlockFile(scope: !1529, file: !1, discriminator: 6)
!1534 = !DILocation(line: 718, column: 3, scope: !1535)
!1535 = !DILexicalBlockFile(scope: !1529, file: !1, discriminator: 7)
!1536 = !DILocation(line: 718, column: 3, scope: !1537)
!1537 = !DILexicalBlockFile(scope: !1529, file: !1, discriminator: 8)
!1538 = !DILocation(line: 718, column: 3, scope: !1539)
!1539 = !DILexicalBlockFile(scope: !1503, file: !1, discriminator: 9)
!1540 = !DILocation(line: 720, column: 3, scope: !1503)
!1541 = !DILocation(line: 722, column: 42, scope: !1503)
!1542 = !DILocation(line: 722, column: 40, scope: !1503)
!1543 = !DILocation(line: 722, column: 15, scope: !1503)
!1544 = !DILocation(line: 722, column: 19, scope: !1503)
!1545 = !DILocation(line: 722, column: 13, scope: !1503)
!1546 = !DILocation(line: 724, column: 28, scope: !1503)
!1547 = !DILocation(line: 724, column: 12, scope: !1503)
!1548 = !DILocation(line: 724, column: 3, scope: !1503)
!1549 = !DILocation(line: 724, column: 7, scope: !1503)
!1550 = !DILocation(line: 724, column: 26, scope: !1503)
!1551 = !DILocation(line: 725, column: 44, scope: !1503)
!1552 = !DILocation(line: 725, column: 30, scope: !1503)
!1553 = !DILocation(line: 725, column: 28, scope: !1503)
!1554 = !DILocation(line: 725, column: 3, scope: !1503)
!1555 = !DILocation(line: 725, column: 7, scope: !1503)
!1556 = !DILocation(line: 725, column: 42, scope: !1503)
!1557 = !DILocation(line: 727, column: 3, scope: !1503)
!1558 = !DILocation(line: 727, column: 3, scope: !1559)
!1559 = !DILexicalBlockFile(scope: !1560, file: !1, discriminator: 1)
!1560 = distinct !DILexicalBlock(scope: !1503, file: !1, line: 727, column: 3)
!1561 = !DILocation(line: 727, column: 3, scope: !1562)
!1562 = !DILexicalBlockFile(scope: !1559, file: !1, discriminator: 2)
!1563 = !DILocation(line: 729, column: 2, scope: !1503)
!1564 = !DILocation(line: 729, column: 11, scope: !1565)
!1565 = !DILexicalBlockFile(scope: !75, file: !1, discriminator: 1)
!1566 = !DILocation(line: 729, column: 20, scope: !1565)
!1567 = !DILocation(line: 729, column: 2, scope: !1565)
!1568 = !DILocation(line: 730, column: 1, scope: !75)
!1569 = !DILocalVariable(name: "mf", arg: 1, scope: !76, file: !1, line: 736, type: !22)
!1570 = !DILocation(line: 736, column: 27, scope: !76)
!1571 = !DILocalVariable(name: "matches", arg: 2, scope: !76, file: !1, line: 736, type: !44)
!1572 = !DILocation(line: 736, column: 43, scope: !76)
!1573 = !DILocalVariable(name: "cur", scope: !76, file: !1, line: 738, type: !96)
!1574 = !DILocation(line: 738, column: 17, scope: !76)
!1575 = !DILocalVariable(name: "pos", scope: !76, file: !1, line: 739, type: !11)
!1576 = !DILocation(line: 739, column: 11, scope: !76)
!1577 = !DILocalVariable(name: "temp", scope: !76, file: !1, line: 740, type: !11)
!1578 = !DILocation(line: 740, column: 11, scope: !76)
!1579 = !DILocalVariable(name: "hash_value", scope: !76, file: !1, line: 740, type: !11)
!1580 = !DILocation(line: 740, column: 17, scope: !76)
!1581 = !DILocalVariable(name: "hash_2_value", scope: !76, file: !1, line: 740, type: !11)
!1582 = !DILocation(line: 740, column: 29, scope: !76)
!1583 = !DILocalVariable(name: "hash_3_value", scope: !76, file: !1, line: 740, type: !11)
!1584 = !DILocation(line: 740, column: 43, scope: !76)
!1585 = !DILocalVariable(name: "delta2", scope: !76, file: !1, line: 741, type: !11)
!1586 = !DILocation(line: 741, column: 11, scope: !76)
!1587 = !DILocalVariable(name: "delta3", scope: !76, file: !1, line: 741, type: !11)
!1588 = !DILocation(line: 741, column: 19, scope: !76)
!1589 = !DILocalVariable(name: "cur_match", scope: !76, file: !1, line: 741, type: !11)
!1590 = !DILocation(line: 741, column: 27, scope: !76)
!1591 = !DILocalVariable(name: "len_best", scope: !76, file: !1, line: 742, type: !11)
!1592 = !DILocation(line: 742, column: 11, scope: !76)
!1593 = !DILocalVariable(name: "matches_count", scope: !76, file: !1, line: 743, type: !11)
!1594 = !DILocation(line: 743, column: 11, scope: !76)
!1595 = !DILocalVariable(name: "len_limit", scope: !76, file: !1, line: 745, type: !11)
!1596 = !DILocation(line: 745, column: 2, scope: !76)
!1597 = !DILocation(line: 745, column: 2, scope: !1598)
!1598 = distinct !DILexicalBlock(scope: !76, file: !1, line: 745, column: 2)
!1599 = !DILocation(line: 745, column: 2, scope: !1600)
!1600 = !DILexicalBlockFile(scope: !1601, file: !1, discriminator: 1)
!1601 = distinct !DILexicalBlock(scope: !1598, file: !1, line: 745, column: 2)
!1602 = !DILocation(line: 745, column: 2, scope: !1603)
!1603 = !DILexicalBlockFile(scope: !1604, file: !1, discriminator: 2)
!1604 = distinct !DILexicalBlock(scope: !1598, file: !1, line: 745, column: 2)
!1605 = !DILocation(line: 745, column: 2, scope: !1606)
!1606 = !DILexicalBlockFile(scope: !1604, file: !1, discriminator: 3)
!1607 = !DILocation(line: 745, column: 2, scope: !1608)
!1608 = !DILexicalBlockFile(scope: !1609, file: !1, discriminator: 4)
!1609 = distinct !DILexicalBlock(scope: !1604, file: !1, line: 745, column: 2)
!1610 = !DILocation(line: 745, column: 2, scope: !1611)
!1611 = !DILexicalBlockFile(scope: !1609, file: !1, discriminator: 5)
!1612 = !DILocation(line: 745, column: 2, scope: !1613)
!1613 = !DILexicalBlockFile(scope: !1609, file: !1, discriminator: 6)
!1614 = !DILocation(line: 745, column: 2, scope: !1615)
!1615 = !DILexicalBlockFile(scope: !1609, file: !1, discriminator: 7)
!1616 = !DILocation(line: 745, column: 2, scope: !1617)
!1617 = !DILexicalBlockFile(scope: !1609, file: !1, discriminator: 8)
!1618 = !DILocation(line: 745, column: 2, scope: !1619)
!1619 = !DILexicalBlockFile(scope: !76, file: !1, discriminator: 9)
!1620 = !DILocation(line: 747, column: 2, scope: !76)
!1621 = !DILocation(line: 749, column: 11, scope: !76)
!1622 = !DILocation(line: 749, column: 26, scope: !76)
!1623 = !DILocation(line: 749, column: 17, scope: !76)
!1624 = !DILocation(line: 749, column: 21, scope: !76)
!1625 = !DILocation(line: 749, column: 15, scope: !76)
!1626 = !DILocation(line: 749, column: 9, scope: !76)
!1627 = !DILocation(line: 750, column: 11, scope: !76)
!1628 = !DILocation(line: 750, column: 44, scope: !76)
!1629 = !DILocation(line: 750, column: 42, scope: !76)
!1630 = !DILocation(line: 750, column: 17, scope: !76)
!1631 = !DILocation(line: 750, column: 21, scope: !76)
!1632 = !DILocation(line: 750, column: 15, scope: !76)
!1633 = !DILocation(line: 750, column: 9, scope: !76)
!1634 = !DILocation(line: 751, column: 41, scope: !76)
!1635 = !DILocation(line: 751, column: 39, scope: !76)
!1636 = !DILocation(line: 751, column: 14, scope: !76)
!1637 = !DILocation(line: 751, column: 18, scope: !76)
!1638 = !DILocation(line: 751, column: 12, scope: !76)
!1639 = !DILocation(line: 753, column: 27, scope: !76)
!1640 = !DILocation(line: 753, column: 11, scope: !76)
!1641 = !DILocation(line: 753, column: 2, scope: !76)
!1642 = !DILocation(line: 753, column: 6, scope: !76)
!1643 = !DILocation(line: 753, column: 25, scope: !76)
!1644 = !DILocation(line: 754, column: 45, scope: !76)
!1645 = !DILocation(line: 754, column: 29, scope: !76)
!1646 = !DILocation(line: 754, column: 27, scope: !76)
!1647 = !DILocation(line: 754, column: 2, scope: !76)
!1648 = !DILocation(line: 754, column: 6, scope: !76)
!1649 = !DILocation(line: 754, column: 43, scope: !76)
!1650 = !DILocation(line: 755, column: 43, scope: !76)
!1651 = !DILocation(line: 755, column: 29, scope: !76)
!1652 = !DILocation(line: 755, column: 27, scope: !76)
!1653 = !DILocation(line: 755, column: 2, scope: !76)
!1654 = !DILocation(line: 755, column: 6, scope: !76)
!1655 = !DILocation(line: 755, column: 41, scope: !76)
!1656 = !DILocation(line: 757, column: 6, scope: !1657)
!1657 = distinct !DILexicalBlock(scope: !76, file: !1, line: 757, column: 6)
!1658 = !DILocation(line: 757, column: 15, scope: !1657)
!1659 = !DILocation(line: 757, column: 19, scope: !1657)
!1660 = !DILocation(line: 757, column: 13, scope: !1657)
!1661 = !DILocation(line: 757, column: 31, scope: !1657)
!1662 = !DILocation(line: 757, column: 36, scope: !1663)
!1663 = !DILexicalBlockFile(scope: !1657, file: !1, discriminator: 1)
!1664 = !DILocation(line: 757, column: 42, scope: !1663)
!1665 = !DILocation(line: 757, column: 40, scope: !1663)
!1666 = !DILocation(line: 757, column: 34, scope: !1663)
!1667 = !DILocation(line: 757, column: 54, scope: !1663)
!1668 = !DILocation(line: 757, column: 53, scope: !1663)
!1669 = !DILocation(line: 757, column: 50, scope: !1663)
!1670 = !DILocation(line: 757, column: 6, scope: !1663)
!1671 = !DILocation(line: 758, column: 12, scope: !1672)
!1672 = distinct !DILexicalBlock(scope: !1657, file: !1, line: 757, column: 59)
!1673 = !DILocation(line: 759, column: 3, scope: !1672)
!1674 = !DILocation(line: 759, column: 14, scope: !1672)
!1675 = !DILocation(line: 759, column: 18, scope: !1672)
!1676 = !DILocation(line: 760, column: 21, scope: !1672)
!1677 = !DILocation(line: 760, column: 28, scope: !1672)
!1678 = !DILocation(line: 760, column: 3, scope: !1672)
!1679 = !DILocation(line: 760, column: 14, scope: !1672)
!1680 = !DILocation(line: 760, column: 19, scope: !1672)
!1681 = !DILocation(line: 761, column: 17, scope: !1672)
!1682 = !DILocation(line: 762, column: 2, scope: !1672)
!1683 = !DILocation(line: 764, column: 6, scope: !1684)
!1684 = distinct !DILexicalBlock(scope: !76, file: !1, line: 764, column: 6)
!1685 = !DILocation(line: 764, column: 16, scope: !1684)
!1686 = !DILocation(line: 764, column: 13, scope: !1684)
!1687 = !DILocation(line: 764, column: 23, scope: !1684)
!1688 = !DILocation(line: 764, column: 26, scope: !1689)
!1689 = !DILexicalBlockFile(scope: !1684, file: !1, discriminator: 1)
!1690 = !DILocation(line: 764, column: 35, scope: !1689)
!1691 = !DILocation(line: 764, column: 39, scope: !1689)
!1692 = !DILocation(line: 764, column: 33, scope: !1689)
!1693 = !DILocation(line: 765, column: 4, scope: !1684)
!1694 = !DILocation(line: 765, column: 9, scope: !1689)
!1695 = !DILocation(line: 765, column: 15, scope: !1689)
!1696 = !DILocation(line: 765, column: 13, scope: !1689)
!1697 = !DILocation(line: 765, column: 7, scope: !1689)
!1698 = !DILocation(line: 765, column: 27, scope: !1689)
!1699 = !DILocation(line: 765, column: 26, scope: !1689)
!1700 = !DILocation(line: 765, column: 23, scope: !1689)
!1701 = !DILocation(line: 764, column: 6, scope: !1702)
!1702 = !DILexicalBlockFile(scope: !76, file: !1, discriminator: 2)
!1703 = !DILocation(line: 766, column: 12, scope: !1704)
!1704 = distinct !DILexicalBlock(scope: !1684, file: !1, line: 765, column: 32)
!1705 = !DILocation(line: 767, column: 35, scope: !1704)
!1706 = !DILocation(line: 767, column: 42, scope: !1704)
!1707 = !DILocation(line: 767, column: 24, scope: !1704)
!1708 = !DILocation(line: 767, column: 3, scope: !1704)
!1709 = !DILocation(line: 767, column: 28, scope: !1704)
!1710 = !DILocation(line: 767, column: 33, scope: !1704)
!1711 = !DILocation(line: 768, column: 12, scope: !1704)
!1712 = !DILocation(line: 768, column: 10, scope: !1704)
!1713 = !DILocation(line: 769, column: 2, scope: !1704)
!1714 = !DILocation(line: 771, column: 6, scope: !1715)
!1715 = distinct !DILexicalBlock(scope: !76, file: !1, line: 771, column: 6)
!1716 = !DILocation(line: 771, column: 20, scope: !1715)
!1717 = !DILocation(line: 771, column: 6, scope: !76)
!1718 = !DILocation(line: 772, column: 3, scope: !1719)
!1719 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 771, column: 26)
!1720 = !DILocation(line: 772, column: 11, scope: !1721)
!1721 = !DILexicalBlockFile(scope: !1722, file: !1, discriminator: 1)
!1722 = distinct !DILexicalBlock(scope: !1723, file: !1, line: 772, column: 3)
!1723 = distinct !DILexicalBlock(scope: !1719, file: !1, line: 772, column: 3)
!1724 = !DILocation(line: 772, column: 23, scope: !1721)
!1725 = !DILocation(line: 772, column: 20, scope: !1721)
!1726 = !DILocation(line: 772, column: 3, scope: !1721)
!1727 = !DILocation(line: 773, column: 10, scope: !1728)
!1728 = distinct !DILexicalBlock(scope: !1722, file: !1, line: 773, column: 8)
!1729 = !DILocation(line: 773, column: 16, scope: !1728)
!1730 = !DILocation(line: 773, column: 14, scope: !1728)
!1731 = !DILocation(line: 773, column: 27, scope: !1728)
!1732 = !DILocation(line: 773, column: 25, scope: !1728)
!1733 = !DILocation(line: 773, column: 8, scope: !1728)
!1734 = !DILocation(line: 773, column: 42, scope: !1728)
!1735 = !DILocation(line: 773, column: 38, scope: !1728)
!1736 = !DILocation(line: 773, column: 35, scope: !1728)
!1737 = !DILocation(line: 773, column: 8, scope: !1722)
!1738 = !DILocation(line: 774, column: 5, scope: !1728)
!1739 = !DILocation(line: 773, column: 50, scope: !1740)
!1740 = !DILexicalBlockFile(scope: !1728, file: !1, discriminator: 1)
!1741 = !DILocation(line: 772, column: 34, scope: !1742)
!1742 = !DILexicalBlockFile(scope: !1722, file: !1, discriminator: 2)
!1743 = !DILocation(line: 772, column: 3, scope: !1742)
!1744 = !DILocation(line: 776, column: 36, scope: !1719)
!1745 = !DILocation(line: 776, column: 11, scope: !1719)
!1746 = !DILocation(line: 776, column: 25, scope: !1719)
!1747 = !DILocation(line: 776, column: 3, scope: !1719)
!1748 = !DILocation(line: 776, column: 30, scope: !1719)
!1749 = !DILocation(line: 776, column: 34, scope: !1719)
!1750 = !DILocation(line: 778, column: 7, scope: !1751)
!1751 = distinct !DILexicalBlock(scope: !1719, file: !1, line: 778, column: 7)
!1752 = !DILocation(line: 778, column: 19, scope: !1751)
!1753 = !DILocation(line: 778, column: 16, scope: !1751)
!1754 = !DILocation(line: 778, column: 7, scope: !1719)
!1755 = !DILocation(line: 779, column: 4, scope: !1756)
!1756 = distinct !DILexicalBlock(scope: !1751, file: !1, line: 778, column: 30)
!1757 = !DILocation(line: 779, column: 4, scope: !1758)
!1758 = !DILexicalBlockFile(scope: !1759, file: !1, discriminator: 1)
!1759 = distinct !DILexicalBlock(scope: !1756, file: !1, line: 779, column: 4)
!1760 = !DILocation(line: 779, column: 4, scope: !1761)
!1761 = !DILexicalBlockFile(scope: !1758, file: !1, discriminator: 2)
!1762 = !DILocation(line: 780, column: 11, scope: !1756)
!1763 = !DILocation(line: 780, column: 4, scope: !1756)
!1764 = !DILocation(line: 782, column: 2, scope: !1719)
!1765 = !DILocation(line: 784, column: 6, scope: !1766)
!1766 = distinct !DILexicalBlock(scope: !76, file: !1, line: 784, column: 6)
!1767 = !DILocation(line: 784, column: 15, scope: !1766)
!1768 = !DILocation(line: 784, column: 6, scope: !76)
!1769 = !DILocation(line: 785, column: 12, scope: !1766)
!1770 = !DILocation(line: 785, column: 3, scope: !1766)
!1771 = !DILocation(line: 787, column: 2, scope: !76)
!1772 = !DILocation(line: 787, column: 2, scope: !1773)
!1773 = !DILexicalBlockFile(scope: !1774, file: !1, discriminator: 1)
!1774 = distinct !DILexicalBlock(scope: !76, file: !1, line: 787, column: 2)
!1775 = !DILocation(line: 787, column: 2, scope: !1776)
!1776 = !DILexicalBlockFile(scope: !1773, file: !1, discriminator: 2)
!1777 = !DILocation(line: 788, column: 1, scope: !76)
!1778 = !DILocalVariable(name: "mf", arg: 1, scope: !77, file: !1, line: 792, type: !22)
!1779 = !DILocation(line: 792, column: 27, scope: !77)
!1780 = !DILocalVariable(name: "amount", arg: 2, scope: !77, file: !1, line: 792, type: !11)
!1781 = !DILocation(line: 792, column: 40, scope: !77)
!1782 = !DILocation(line: 794, column: 2, scope: !77)
!1783 = !DILocalVariable(name: "cur", scope: !1784, file: !1, line: 795, type: !96)
!1784 = distinct !DILexicalBlock(scope: !77, file: !1, line: 794, column: 5)
!1785 = !DILocation(line: 795, column: 18, scope: !1784)
!1786 = !DILocalVariable(name: "pos", scope: !1784, file: !1, line: 796, type: !11)
!1787 = !DILocation(line: 796, column: 12, scope: !1784)
!1788 = !DILocalVariable(name: "temp", scope: !1784, file: !1, line: 797, type: !11)
!1789 = !DILocation(line: 797, column: 12, scope: !1784)
!1790 = !DILocalVariable(name: "hash_value", scope: !1784, file: !1, line: 797, type: !11)
!1791 = !DILocation(line: 797, column: 18, scope: !1784)
!1792 = !DILocalVariable(name: "hash_2_value", scope: !1784, file: !1, line: 797, type: !11)
!1793 = !DILocation(line: 797, column: 30, scope: !1784)
!1794 = !DILocalVariable(name: "hash_3_value", scope: !1784, file: !1, line: 797, type: !11)
!1795 = !DILocation(line: 797, column: 44, scope: !1784)
!1796 = !DILocalVariable(name: "cur_match", scope: !1784, file: !1, line: 798, type: !11)
!1797 = !DILocation(line: 798, column: 12, scope: !1784)
!1798 = !DILocalVariable(name: "len_limit", scope: !1784, file: !1, line: 800, type: !11)
!1799 = !DILocation(line: 800, column: 3, scope: !1784)
!1800 = !DILocation(line: 800, column: 3, scope: !1801)
!1801 = distinct !DILexicalBlock(scope: !1784, file: !1, line: 800, column: 3)
!1802 = !DILocation(line: 800, column: 3, scope: !1803)
!1803 = !DILexicalBlockFile(scope: !1804, file: !1, discriminator: 1)
!1804 = distinct !DILexicalBlock(scope: !1801, file: !1, line: 800, column: 3)
!1805 = !DILocation(line: 800, column: 3, scope: !1806)
!1806 = !DILexicalBlockFile(scope: !1807, file: !1, discriminator: 2)
!1807 = distinct !DILexicalBlock(scope: !1801, file: !1, line: 800, column: 3)
!1808 = !DILocation(line: 800, column: 3, scope: !1809)
!1809 = !DILexicalBlockFile(scope: !1807, file: !1, discriminator: 3)
!1810 = !DILocation(line: 800, column: 3, scope: !1811)
!1811 = !DILexicalBlockFile(scope: !1812, file: !1, discriminator: 4)
!1812 = distinct !DILexicalBlock(scope: !1807, file: !1, line: 800, column: 3)
!1813 = !DILocation(line: 800, column: 3, scope: !1814)
!1814 = !DILexicalBlockFile(scope: !1812, file: !1, discriminator: 5)
!1815 = !DILocation(line: 800, column: 3, scope: !1816)
!1816 = !DILexicalBlockFile(scope: !1812, file: !1, discriminator: 6)
!1817 = !DILocation(line: 800, column: 3, scope: !1818)
!1818 = !DILexicalBlockFile(scope: !1812, file: !1, discriminator: 7)
!1819 = !DILocation(line: 800, column: 3, scope: !1820)
!1820 = !DILexicalBlockFile(scope: !1812, file: !1, discriminator: 8)
!1821 = !DILocation(line: 800, column: 3, scope: !1822)
!1822 = !DILexicalBlockFile(scope: !1784, file: !1, discriminator: 9)
!1823 = !DILocation(line: 802, column: 3, scope: !1784)
!1824 = !DILocation(line: 804, column: 42, scope: !1784)
!1825 = !DILocation(line: 804, column: 40, scope: !1784)
!1826 = !DILocation(line: 804, column: 15, scope: !1784)
!1827 = !DILocation(line: 804, column: 19, scope: !1784)
!1828 = !DILocation(line: 804, column: 13, scope: !1784)
!1829 = !DILocation(line: 806, column: 28, scope: !1784)
!1830 = !DILocation(line: 806, column: 12, scope: !1784)
!1831 = !DILocation(line: 806, column: 3, scope: !1784)
!1832 = !DILocation(line: 806, column: 7, scope: !1784)
!1833 = !DILocation(line: 806, column: 26, scope: !1784)
!1834 = !DILocation(line: 807, column: 46, scope: !1784)
!1835 = !DILocation(line: 807, column: 30, scope: !1784)
!1836 = !DILocation(line: 807, column: 28, scope: !1784)
!1837 = !DILocation(line: 807, column: 3, scope: !1784)
!1838 = !DILocation(line: 807, column: 7, scope: !1784)
!1839 = !DILocation(line: 807, column: 44, scope: !1784)
!1840 = !DILocation(line: 808, column: 44, scope: !1784)
!1841 = !DILocation(line: 808, column: 30, scope: !1784)
!1842 = !DILocation(line: 808, column: 28, scope: !1784)
!1843 = !DILocation(line: 808, column: 3, scope: !1784)
!1844 = !DILocation(line: 808, column: 7, scope: !1784)
!1845 = !DILocation(line: 808, column: 42, scope: !1784)
!1846 = !DILocation(line: 810, column: 3, scope: !1784)
!1847 = !DILocation(line: 810, column: 3, scope: !1848)
!1848 = !DILexicalBlockFile(scope: !1849, file: !1, discriminator: 1)
!1849 = distinct !DILexicalBlock(scope: !1784, file: !1, line: 810, column: 3)
!1850 = !DILocation(line: 810, column: 3, scope: !1851)
!1851 = !DILexicalBlockFile(scope: !1848, file: !1, discriminator: 2)
!1852 = !DILocation(line: 812, column: 2, scope: !1784)
!1853 = !DILocation(line: 812, column: 11, scope: !1854)
!1854 = !DILexicalBlockFile(scope: !77, file: !1, discriminator: 1)
!1855 = !DILocation(line: 812, column: 20, scope: !1854)
!1856 = !DILocation(line: 812, column: 2, scope: !1854)
!1857 = !DILocation(line: 813, column: 1, scope: !77)
!1858 = !DILocalVariable(name: "mf", arg: 1, scope: !90, file: !1, line: 113, type: !22)
!1859 = !DILocation(line: 113, column: 20, scope: !90)
!1860 = !DILocalVariable(name: "i", scope: !90, file: !1, line: 115, type: !11)
!1861 = !DILocation(line: 115, column: 11, scope: !90)
!1862 = !DILocalVariable(name: "subvalue", scope: !90, file: !1, line: 116, type: !11)
!1863 = !DILocation(line: 116, column: 11, scope: !90)
!1864 = !DILocalVariable(name: "count", scope: !90, file: !1, line: 117, type: !11)
!1865 = !DILocation(line: 117, column: 11, scope: !90)
!1866 = !DILocalVariable(name: "hash", scope: !90, file: !1, line: 118, type: !55)
!1867 = !DILocation(line: 118, column: 12, scope: !90)
!1868 = !DILocation(line: 120, column: 2, scope: !90)
!1869 = !DILocation(line: 120, column: 2, scope: !1870)
!1870 = !DILexicalBlockFile(scope: !90, file: !1, discriminator: 1)
!1871 = !DILocation(line: 120, column: 2, scope: !1872)
!1872 = !DILexicalBlockFile(scope: !90, file: !1, discriminator: 2)
!1873 = !DILocation(line: 120, column: 2, scope: !1874)
!1874 = !DILexicalBlockFile(scope: !90, file: !1, discriminator: 3)
!1875 = !DILocation(line: 124, column: 35, scope: !90)
!1876 = !DILocation(line: 124, column: 39, scope: !90)
!1877 = !DILocation(line: 124, column: 33, scope: !90)
!1878 = !DILocation(line: 124, column: 11, scope: !90)
!1879 = !DILocation(line: 127, column: 10, scope: !90)
!1880 = !DILocation(line: 127, column: 14, scope: !90)
!1881 = !DILocation(line: 127, column: 30, scope: !90)
!1882 = !DILocation(line: 127, column: 34, scope: !90)
!1883 = !DILocation(line: 127, column: 28, scope: !90)
!1884 = !DILocation(line: 127, column: 8, scope: !90)
!1885 = !DILocation(line: 128, column: 9, scope: !90)
!1886 = !DILocation(line: 128, column: 13, scope: !90)
!1887 = !DILocation(line: 128, column: 7, scope: !90)
!1888 = !DILocation(line: 130, column: 9, scope: !1889)
!1889 = distinct !DILexicalBlock(scope: !90, file: !1, line: 130, column: 2)
!1890 = !DILocation(line: 130, column: 7, scope: !1889)
!1891 = !DILocation(line: 130, column: 14, scope: !1892)
!1892 = !DILexicalBlockFile(scope: !1893, file: !1, discriminator: 1)
!1893 = distinct !DILexicalBlock(scope: !1889, file: !1, line: 130, column: 2)
!1894 = !DILocation(line: 130, column: 18, scope: !1892)
!1895 = !DILocation(line: 130, column: 16, scope: !1892)
!1896 = !DILocation(line: 130, column: 2, scope: !1892)
!1897 = !DILocation(line: 141, column: 12, scope: !1898)
!1898 = distinct !DILexicalBlock(scope: !1899, file: !1, line: 141, column: 7)
!1899 = distinct !DILexicalBlock(scope: !1893, file: !1, line: 130, column: 30)
!1900 = !DILocation(line: 141, column: 7, scope: !1898)
!1901 = !DILocation(line: 141, column: 18, scope: !1898)
!1902 = !DILocation(line: 141, column: 15, scope: !1898)
!1903 = !DILocation(line: 141, column: 7, scope: !1899)
!1904 = !DILocation(line: 142, column: 9, scope: !1898)
!1905 = !DILocation(line: 142, column: 4, scope: !1898)
!1906 = !DILocation(line: 142, column: 12, scope: !1898)
!1907 = !DILocation(line: 144, column: 15, scope: !1898)
!1908 = !DILocation(line: 144, column: 9, scope: !1898)
!1909 = !DILocation(line: 144, column: 4, scope: !1898)
!1910 = !DILocation(line: 144, column: 12, scope: !1898)
!1911 = !DILocation(line: 145, column: 2, scope: !1899)
!1912 = !DILocation(line: 130, column: 25, scope: !1913)
!1913 = !DILexicalBlockFile(scope: !1893, file: !1, discriminator: 2)
!1914 = !DILocation(line: 130, column: 2, scope: !1913)
!1915 = !DILocation(line: 148, column: 16, scope: !90)
!1916 = !DILocation(line: 148, column: 2, scope: !90)
!1917 = !DILocation(line: 148, column: 6, scope: !90)
!1918 = !DILocation(line: 148, column: 13, scope: !90)
!1919 = !DILocation(line: 150, column: 2, scope: !90)
